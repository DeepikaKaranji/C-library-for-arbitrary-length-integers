#include "intal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>




static inline void strip_zero(char *a){
    int i = 0;
    for(int j = 0; a[j]!= '\0'; j++)
    {
        if(a[j] != '0') break;
        i++;
    }
    if(a[i] != '\0')
    {
        int j = 0;
        while(a[i]!='\0')
        {
            a[j] = a[i];
            i++;
            j++;
        }
        a[j] = '\0';
    }
    else
    {
        a[1] = '\0'; 
        return;
    }
}

static inline char* make_zero(){
    int num = 2;
    char *ans = (char *)malloc(sizeof(char)*(num));
    ans[0] = '0';
    ans[1] = '\0';
    return ans;
}

static char * itostr(long long int n){
    if(n != 0)
    {
        int x =1, y = 0;
        int cond = (int)(n/x);
        while(cond){
            x *= 10;
            y++;
            cond = (int)(n/x);
        }
        char *answer = (char *)malloc(sizeof(char)*(y+1));
        answer[y] = '\0';
        for(y = y-1; y>=0; y--)
        {
            answer[y] = n%10 + '0';
            n /= 10;
        }
        strip_zero(answer);
        return answer;
    }
    else return make_zero();
    
}

static inline int max(int a, int b){
    if(a>b) return a;
    else return b;
}


char* intal_add(const char* intal1, const char* intal2){
    char *s1 = (char *)malloc(sizeof(char)*(strlen(intal1)+1));
    char *s2 = (char *)malloc(sizeof(char)*(strlen(intal2)+1));

    strcpy(s1,intal1);
    strcpy(s2,intal2);

    strip_zero(s1);
    strip_zero(s2);

    int l1 = strlen(s1);
    int l2 = strlen(s2);
    int foo = max(l1,l2)+2;

    char *answer = (char *)malloc(sizeof(char)*(foo));
    answer[0] = '0';answer[1] = '0';answer[2] = '0';
    int carry = 0;
    int i = l1-1, j = l2-1, k = foo-2;
    answer[foo-1] = '\0';

    while(i>=0 && j>=0){
        int sum_val = s1[i]-'0' + s2[j] - '0' + carry;
        carry = sum_val / 10;
        sum_val %= 10;
        answer[k] = sum_val + '0';
        i--;
        j--;
        k--;
    }
    for(;i>=0; i--,k--)
    {
        int sum_val = s1[i] - '0';
        sum_val += carry;
        carry = sum_val / 10;
        sum_val %= 10;
        answer[k] = sum_val + '0';
    }
    for(; j>=0;j--, k--)
    {
        int sum_val = s2[j] - '0';
        sum_val += carry;
        carry = sum_val / 10;
        sum_val %= 10;
        answer[k] = sum_val + '0';
    }
    if(!(!carry)){
        answer[k] = carry + '0';
    }
    strip_zero(answer);
    free(s1);
    free(s2);
    return answer;
}



int intal_compare(const char* intal1, const char* intal2){
    char *a = (char *)malloc(sizeof(char)*(strlen(intal1)+1));
    char *b = (char *)malloc(sizeof(char)*(strlen(intal2)+1));

    strcpy(a,intal1);
    strcpy(b,intal2);
    strip_zero(a);
    strip_zero(b);
    int l1 = strlen(a), l2 = strlen(b);

    if(l1==l2)
        for(int i = 0; i< l1; i++)
        {
            if(b[i]>a[i]){
                free(a);
                free(b);
                return -1;
                
            }
            else if(b[i]<a[i]){
                free(a);
                free(b);
                return 1;
            }
        }
    free(a);
    free(b);
    if(l1 > l2) return 1;
    else if(l1 == l2) return 0;
    else return -1;
}



char* intal_diff(const char* intal1, const char* intal2){
    char *a = (char *)malloc(sizeof(char)*(strlen(intal1)+1));
    char *b = (char *)malloc(sizeof(char)*(strlen(intal2)+1));

    strcpy(a,intal1);
    strcpy(b,intal2);
    strip_zero(a);
    strip_zero(b);

    int cmp_val = intal_compare(a,b);
    if(cmp_val == 0){
        free(a);
        free(b);
        return make_zero();
    }
    if(cmp_val < 0){
        char * c = a;
        a = b;
        b = c;
    }
    
    int l1 = strlen(a);
    int l2 = strlen(b);
    int foo = max(l1,l2)+3-1;

    // calloc didnt work, not sure why
    char *answer = (char *)malloc(sizeof(char)*(foo));
    int loop = 0;
    while(loop < foo){
        answer[loop] = '0';
        loop++;
    }
    answer[foo-1] = '\0';
    int carry = 0;
    int i = l1-1, j = l2-1 ,k = foo-2 ;
    while(i>=0 && j>=0){
        int a_of_i = a[i] - '0';
        int b_of_j = b[j] - '0';
        if(carry){
            if(a_of_i == 0){
                i--;
                j--;
                answer[k] = 9 - b_of_j + '0';
                k--; 
                continue;
            }
            carry = 0;
            a_of_i--;
        }
        if(a_of_i < b_of_j){
            carry = 1;
            answer[k] = 10 + a_of_i - b_of_j + '0';
        }
        else{
            answer[k] = a_of_i - b_of_j + '0';
        }
        i--;
        j--;
        k--;
    }
    int cond = i>=0;
    while(cond){
        int a_of_i = a[i] - '0';
        if(carry){
            if(a_of_i == 0){
                answer[k] = 9 + '0';
                i--;
                j--;
                k--;     
                continue;
            }
            carry = 0;
            a_of_i--;
        }
        answer[k] = a_of_i + '0';
        i--;
        k--;
        cond = i>=0;
    }
    strip_zero(answer);
    free(a); free(b);
    return answer;
}


char* intal_multiply(const char* intal1, const char* intal2){
    char *a = (char *)malloc(sizeof(char)*(strlen(intal1)+1));
    char *b = (char *)malloc(sizeof(char)*(strlen(intal2)+1));
    strcpy(a,intal1);
    strcpy(b,intal2);
    strip_zero(a);
    strip_zero(b);

    if(a[0] != '0' && b[0] != '0')
    {
        int l1 = strlen(a);
        int l2 = strlen(b);
        int foo = l1+l2+2;
        char *answer = (char *)malloc(sizeof(char)*(foo));
        answer[0] = '\0';
        int answerult[l1+l2];
        memset(answerult,0,sizeof(int)*(l1+l2));
        int l1_i = 0;
        int l2_i = 0;
        int i = l1 - 1;
        while(i >=0)
        {
            int carry = 0;
            int l1_temp = a[i] - '0';
            l2_i = 0;
            int j = l2 - 1;
            while(j>=0)
            {
                int l2_temp = b[j] - '0';
                int sum = l1_temp*l2_temp + answerult[l1_i + l2_i] + carry;
                carry = sum/10;
                answerult[l1_i + l2_i] = (sum % 10);
                l2_i++;
                j--;
            }
            if (carry > 0)
                answerult[l1_i + l2_i] += carry;
            l1_i++;
            i--;
        }
        i = l1+l2-1;
        for(; i>=0 && answerult[i] == 0;i--);
        // while (i>=0 && answerult[i] == 0)
        //     i--;
        if (i != -1)
        {
            while (i >= 0)
            {
                char *x = itostr(answerult[i--]);
                strcat(answer,x);
                free(x);
            }
            strip_zero(answer);
            free(a);
            free(b);
            return answer;
        }
        else
        {
            free(a);
            free(b);
            return make_zero();
        }
        
        
    }
    else
    {
        free(a);
        free(b);
        return make_zero();
    }
    
}





static char* intal_divide(const char* intal1, const char* intal2){
    char *a = (char *)malloc(sizeof(char)*(strlen(intal1)+1));
    char *b = (char *)malloc(sizeof(char)*(strlen(intal2)+1));

    strcpy(a,intal1);
    strcpy(b,intal2);
    strip_zero(a);
    strip_zero(b);
    
    if(a[0] == '0')
    {
        free(a);
        free(b);
        return make_zero();
    }
    if(b[0] == '0'){
        fprintf(stderr, "ERROR: Division by zero %s\n", b);
        exit(-1);
    }
    int cmp = intal_compare(a,b);

        if(cmp == 0){
        char *answer = make_zero();
        answer[0] = '1';
        free(a); free(b);
        return answer;
    }
    if(cmp < 0){
        free(a); free(b);
        return make_zero();
    }
    
    else
    {
        int n = strlen(a);
        char *answer = make_zero();
        
        char *d = make_zero();
        long long i = 0, j = 1, flag = 0;
        char *str10 = itostr(10);
        while(i<(int)n)
        {
            flag = 0;
            while(intal_compare(d,b)<0 && i<(int)n)
            {
                char *t = d;
                d = intal_multiply(d, str10) ;
                free(t);
                t = d;
                char *x = itostr(a[i]-'0');
                d = intal_add(d, x);
                free(x);free(t);
                flag++;
                i++;
            }
            j = 1;
            flag--;
            char *j_char = itostr(j);
            char *x = intal_multiply(b, j_char);
        
            for(;intal_compare(x,d)<0;)
            {
                j++;
                free(j_char);free(x);
                j_char = itostr(j);
                x = intal_multiply(b, j_char);
            }
            if(intal_compare(x, d)>0)
                j--;

            for(;flag > 0;flag--)
            {
                char *ans = answer;
                answer = intal_multiply(ans,str10);
                free(ans);
                // flag--;
            }
            free(j_char);free(x);
            char *ans = answer;
            answer = intal_multiply(ans,str10);
            free(ans);
            ans = answer;
            j_char = itostr(j);
            answer = intal_add(ans, j_char);
            free(ans);
            char *w = d;
            x = intal_multiply(b, j_char);
            d = intal_diff(w, x);
            free(w); 
            free(j_char); 
            free(x);
        }
        strip_zero(answer);
        free(a); free(b);free(d); free(str10);
        return answer;
    }

}

char* intal_mod(const char* intal1, const char* intal2){
    char *a = (char *)malloc(sizeof(char)*(strlen(intal1)+1));
    char *b = (char *)malloc(sizeof(char)*(strlen(intal2)+1));

    strcpy(a,intal1);
    strcpy(b,intal2);
    strip_zero(a);
    strip_zero(b);

    char *quotient = intal_divide(a,b);
    char *prod = intal_multiply(b,quotient);
    char *mod_val = intal_diff(a,prod);
    free(quotient);
    free(prod);
    free(a);
    free(b);
    return mod_val;
}



char* intal_pow(const char* intal1, unsigned int n){
    char *a = (char *)malloc(sizeof(char)*(strlen(intal1)+1));
    strcpy(a,intal1);
    strip_zero(a);
    
    if(n==0){
        free(a);
        return itostr(1);
    }
    if(n==1){
        return a;
    }

    else
    {
        char *answer = itostr(1);
        for(; n>0; n/=2)
        {
            if(n&1)
            {
                char *temp = answer;
                answer = intal_multiply(temp, a);
                free(temp);
            }
            char *temp = a;
            a = intal_multiply(temp, a);
            free(temp);            
        }
        strip_zero(answer);
        free(a);
        return answer;
    }
    

}

char* intal_gcd(const char* intal1, const char* intal2){
    char *a = (char *)malloc(sizeof(char)*(strlen(intal1)+1));
    char *b = (char *)malloc(sizeof(char)*(strlen(intal2)+1));
    strcpy(a,intal1);
    strcpy(b,intal2);
    strip_zero(a);
    strip_zero(b);

    if(b[0] != '0'){
        char *mod_val = intal_mod(a,b);
        char *answer = intal_gcd(b, mod_val);
        free(a);
        free(b);
        free(mod_val);
        return answer;
    }
    else
    {
        free(b);
        return a;
    }
}


char* intal_fibonacci(unsigned int n)
{
    if(n == 0) return itostr(0);
    if(n == 1 || n == 2) return itostr(1);
    else
    {
        char *x = itostr(0);
        char *y = itostr(1);
        char *z = itostr(1);
        for(int i=n-2; i>0; i--)
        {
            free(x);
            x = y;
            y = z;
            z = intal_add(x,y);
        }
        free(x);
        free(y);
        return z;
    }


}


static char* collect(unsigned int x, unsigned int y)
{
    int one = 1;
    if(y-x !=1*one && x!=y)
    {
        char *x_char = collect(x, x + -(x-y)/2-1);
        char *y_char = collect(x + -(x-y)/2, y);
        char *z_char = intal_multiply(x_char,y_char);
        free(x_char);
        free(y_char);
        return z_char;
    }
    if(x==y) return itostr(y);

    else
    {
            char *x_char = itostr(x);
            char *y_char = itostr(y);
            char *z_char = intal_multiply(x_char,y_char);
            free(x_char);
            free(y_char);
            return z_char;
        
    }
}

char* intal_factorial(unsigned int n){
    if(n == 0) return itostr(1);
    return collect(1, n);
}

int swap_uint(unsigned int x, unsigned int y){

    unsigned int *a = &x;
    unsigned int *b = &y;
    unsigned int temp = *a;
    *a = *b;
    *b = temp;
    return 1;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
    if(k > n) return make_zero();
    if((n == 0 || k == 0) || n == k) return itostr(1);
    else
    {   
        int one = 1;
        unsigned int i = n - k;
        if(k > i){
            swap_uint(k,i);
        }
        char *fact = intal_factorial(k);
        char *collected = collect(i+one, n);
        char *answer = intal_divide(collected,fact);
        free(collected);
        free(fact);
        return answer;
    }
}

int intal_max(char **arr, int n)
{
    if(n < 0 || n == 0) return -1;
    else
    {
        int answer = 0;
        int i = 1;
        while(i<n)
        {
            if(intal_compare(arr[i], arr[answer]) == 1)
            {
                answer = i;
            }
            i++;
        }
        return answer;
    }
    
}



int intal_min(char **arr, int n)
{
    if(n < 0 || n == 0) return -1;
    else
    {
        int answer = 0;
        int i = 1;
        while(i<n)
        {
            if(intal_compare(arr[i], arr[answer]) == -1)
            {
                answer = i;
            }
            i++;
        }
        return answer;
    }
}


int intal_search(char **arr, int n, const char* key){
    if(n<=0) return -1;
    for(int i = 0; i < n; i++){
        if(intal_compare(arr[i], key) == 0){
            return i;
        }
    }
    return -1;
}


int intal_binsearch(char **arr, int n, const char* key){
    if(n<=0) return -1;
    int lb = 0;
    int ub = n;
    int one = 1;
    while(ub >= lb)
    {
        int mid = lb + (ub-lb)/2*one;
        int tmp = intal_compare(arr[mid], key);
        if((mid == 0 || intal_compare(arr[mid-1], key) == -1*one) && tmp == 0) 
            return mid;
        else if(tmp == 1*one) 
            ub = mid - 1;
        else lb = mid + 1;
    }
    return -1;
}

static void merger_func(int x, int m, int y,char **arr){
    char **tmp = (char **)malloc(sizeof(char *)*(m-x+1));
    int i = x;
    while(i < m){
        tmp[i-x] = arr[i];
        i++;
    }

    i = m;
    int j = x, k=0;
    int cond = (i<y) &&  k<(m-x);
    while(cond)
    {
        int cmp = intal_compare(arr[i], tmp[k]);
        if(cmp ==1 || cmp ==0)
        {
            arr[j] = tmp[k];
            j++;
            k++;
        }
        else
        {
            arr[j] = arr[i];
            j++;
            i++;
        }
        cond = (i<y) &&  k<(m-x);
        // printf("cond:%d\n", cond);        
    }
    for(;k<(m-x); k++, j++)
    {
        arr[j] = tmp[k];
    }
    free(tmp);
}



static void merge_sort(int x, int y, char **arr){
    if(y-x<1){
        return;
    }
    else if(y - x > 1)
    {
        int m = x + (y-x)/2;
        merge_sort(x,m,arr);
        merge_sort(m,y,arr);
        merger_func(x, m, y, arr);
    }
}
void intal_sort(char **arr, int n){
    merge_sort(0,n,arr);
}


char* coin_row_problem(char **arr, int n)
{
    if(n<=0) {
        return make_zero();
    }
    if(n<2 || n == 2){
        int max = intal_max(arr,n);
        char *answer = (char *)malloc(sizeof(char)*(strlen(arr[max])+1));
        strcpy(answer,arr[max]);
        return answer;
    }

    else
    {
        char *x = (char *)malloc(sizeof(char)*(strlen(arr[0])+1));
        strcpy(x,arr[0]);
        int cmp = intal_compare(x,arr[1]);
        char *y;
        if(cmp > 0){
            y = x;         
        }
        else
        {
            y = (char *)malloc(sizeof(char)*(strlen(arr[1])+1));
            strcpy(y,arr[1]);
        }
        strip_zero(x);
        strip_zero(y);
        int i = 2;
        int one = 1;
        while(i<n)
        {
            char *sum = intal_add(arr[i], x);
            if(x!=y)free(x);
            x = y;
            int cmp = intal_compare(sum, y);
            if(cmp == 1*one)
            {
                y = sum;
            }
            else
            {
                free(sum);
            }
            i++;
        }
        cmp = intal_compare(x,y);
        if(cmp == 0 || cmp == 1){
            if(x!=y) free(y);
            return x;
        }
        if(x!=y) free(x);
        return y;
    }

    
    
}



