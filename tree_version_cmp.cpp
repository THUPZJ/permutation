#include <vector>
#include <stack>
#include <cstdio>
#include <iostream>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

typedef vector<int>* (*PMF[])(int,int);


long long factorial[] = {1ll,1ll,2ll,6ll,24ll,120ll,720ll,5040ll,40320ll,362880ll,3628800ll,39916800ll,479001600ll,6227020800ll,87178291200ll,1307674368000ll,20922789888000ll,355687428096000ll,6402373705728000ll,121645100408832000ll,2432902008176640000ll};

double getTimeStamp()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (t.tv_sec * 1000000 + t.tv_usec) * 1e-6;
}

class PermutationEndException
{
public:
    PermutationEndException(){};
};

struct BTNode{
    int num;
    int count;
    BTNode* left;
    BTNode* right;
    BTNode(){num=0;left=NULL;right=NULL;}
};



void _permutation_Recur(vector<int>* A,int start,int end)
{
    if(start==end)
    {
        //        for(int i=0;i<A->size();i++)
        //            cout<<(*A)[i]<<" ";
        //        cout<<endl;
        return;
    }
    for(int i=start;i<=end;i++)
    {
        swap((*A)[i],(*A)[start]);
        _permutation_Recur(A, start+1, end);
        swap((*A)[i], (*A)[start]);
    }
}

vector<int>* permutation_Recur(int n)
{
    vector<int>* A = new vector<int>(n);
    for(int i=0;i<n;i++)
        (*A)[i] = i+1;
    _permutation_Recur(A, 0, n-1);
    return A;
}

vector<int>* permutation_Dict(int n)
{
    vector<int>* A = new vector<int>(n);
    for(int i=0;i<n;i++)
        (*A)[i] = i+1;
    while(true)
    {
        //        for(int i=0;i<A->size();i++)
        //            cout<<(*A)[i]<<" ";
        //        cout<<endl;
        int j;
        for(j=A->size()-2;j>=0;j--)
        {
            if((*A)[j]<(*A)[j+1])
                break;
            
        }
        if(j<0)
            return A;
        for(int i=A->size()-1;i>j;i--)
        {
            if((*A)[i]>(*A)[j])
            {
                swap((*A)[i],(*A)[j]);
                break;
            }
        }
        int start=j+1,end=A->size()-1;
        while(start<=end)
        {
            swap((*A)[start],(*A)[end]);
            start++;
            end--;
        }
        
    }
}

bool findLargestMobileNumber(vector<int>& A,vector<int>& direction,int &index,int &dire)
{
    int max=-1;
    if(direction[0]==1&&A[0]>A[1])
    {
        max=A[0];
        index=0;
        dire=direction[0];
    }
    for(int i=1;i<A.size()-1;i++)
    {
        if(direction[i]==0)
        {
            if(A[i]>A[i-1]&&A[i]>max)
            {
                max=A[i];
                index=i;
                dire=0;
            }
        }
        else
        {
            if(A[i]>A[i+1]&&A[i]>max)
            {
                max=A[i];
                index=i;
                dire=1;
            }
        }
    }
    if(direction[A.size()-1]==0&&A[A.size()-1]>A[A.size()-2]&&(A[A.size()-1]>max))
    {
        max=A[A.size()-1];
        index=A.size()-1;
        dire=0;
    }
    if(max==-1)
        return false;
    return true;
}

vector<int>* permutation_SJT(int n)
{
    vector<int>* A = new vector<int>(n);
    vector<int> direction(n, 0);
    for(int i=0; i<n; i++)
    {
        (*A)[i] = i + 1;
    }
    // cout<<direction.size();
    int index=0,dire=0,tune=0;
    while(true)
    {
        //        for(int i=0;i<A->size();i++)
        //        {
        //            cout<<(*A)[i]<<" ";
        //        }
        //        cout<<endl;
        bool flag=findLargestMobileNumber(*A, direction, index, dire);
        if(flag==0)
        {
            return A;
        }
        if(dire==0)
        {
            swap((*A)[index],(*A)[index-1]);
            swap(direction[index],direction[index-1]);
            tune=-1;
        }
        else
        {
            swap((*A)[index], (*A)[index+1]);
            swap(direction[index],direction[index+1]);
            tune=1;
        }
        for(int i=0;i<A->size();i++)
        {
            if(i!=index && (*A)[i]> (*A)[index+tune])
            {
                if(direction[i]==0)
                    direction[i]=1;
                else
                    direction[i]=0;
            }
            // direction[i]=!direction[i];
        }
    }
}

int findLMN(int n, int i)
{
    int m = i % n;
    while(m == 0)
    {
        i = i / n;
        n--;
        m = i % n;
    }
    return n;
}

vector<int>* permutation_SJT_improve(int n)
{
    vector<int>* A = new vector<int>(n);
    vector<int> direction(n, 0);
    for(int i=0; i<n; i++)
    {
        (*A)[i] = i + 1;
    }
    vector<int> inv(n+1);
    vector<long long> count(n+1, 0);
    for(int i=1; i<n+1; i++)
    {
        inv[i] = i-1;
    }
    int i = 1;
    while(i<factorial[n])
    {
        int lmn = findLMN(n,i);
        int dir = (((count[lmn] / (lmn-1)) % 2) << 1) - 1; //-1 for left; 1 for right
        count[lmn]++;
        int index = inv[lmn];
        swap((*A)[index], (*A)[index+dir]);
        swap(inv[(*A)[index]], inv[(*A)[index+dir]]);
        i++;
        //        for(int i=0;i<n; i++)
        //        {
        //            cout<<(*A)[i]<<",";
        //        }
        //        cout<<endl;
    }
    return A;
}


vector<int>& nextIncreInterNumber(vector<int>& interNumber)
{
    int size=interNumber.size();
    int carry=0;
    interNumber[size-1]+=1;
    int i;
    for(i=0;i<size;i++)
    {
        interNumber[size-1-i]+=carry;
        if(interNumber[size-1-i]>=(i+2))
        {
            carry=1;
            interNumber[size-1-i]-=(i+2);
        }
        else
        {
            carry = 0;
            break;
        }
    }
    if (i == size and carry == 1)
        throw PermutationEndException();
    return interNumber;
}

vector<int>& nextDecreInterNumber(vector<int>& interNumber)
{
    int size=interNumber.size();
    int carry=0;
    interNumber[size-1]+=1;
    int i;
    for(i=0;i<size;i++)
    {
        interNumber[size-1-i]+=carry;
        if(interNumber[size-1-i]>(size-i))
        {
            carry=1;
            interNumber[size-1-i]-=(size+1-i);
        }
        else
        {
            carry = 0;
            break;
        }
    }
    if (i == size and carry == 1)
        throw PermutationEndException();
    return interNumber;
}


vector<int>* getPermutationDict(vector<int>& interNumber)
{
    vector<bool> shw(interNumber.size()+2, false);
    vector<int>* ans = new vector<int>();
    for(int i=0; i<interNumber.size(); i++)
    {
        int num = interNumber[i] + 1;
        int new_num = num;
        for(int i=1; i<=num; i++)
        {
            if (shw[i])
                new_num++;
        }
        for(; shw[new_num]; new_num++);
        ans->push_back(new_num);
        shw[new_num] = true;
    }
    for(int i=1; i<shw.size(); i++)
    {
        if (!shw[i])
        {
            ans->push_back(i);
            break;
        }
    }
    return ans;
}


vector<int>* getPermutationIncre(vector<int>& interNumber)
{
    vector<int>* ans = new vector<int>(interNumber.size()+1, 1);
    for (int i=0; i<interNumber.size(); i++)
    {
        int num = -1;
        int j;
        for(j=ans->size()-1; j>=0; j--)
            if ((*ans)[j] == 1)
                break;
        
        for(; j>=0; j--)
        {
            if ((*ans)[j] == 1)
                num++;
            else continue;
            if (num == interNumber[i])
            {
                (*ans)[j] = interNumber.size()+1-i;
                break;
            }
        }
    }
    return ans;
}



vector<int>* getPermutationIncreTree(vector<int>& interNumber)
{
    int n = interNumber.size();
    vector<BTNode> nodes(n+1);
    BTNode* root = &nodes[0];
    int j = 1;
    root->count = n+1;
    for(int i=0; i<n ;i++)
    {
        BTNode* now = root;
        int inum = interNumber[i];
        while (true)
        {
            if (now->num == 0)
            {
                now->num = n+1-i;
                now->count--;
                if(inum>0)
                {
                    now->right = &nodes[j++];
                    now->right->count = inum;
                }
                int lc = now->count - inum;
                if(lc>0)
                {
                    now->left = &nodes[j++];
                    now->left->count = lc;
                }
                break;
            }
            else if (now->right and inum < now->right->count)
            {
                now->count--;
                now = now->right;
            }
            else
            {
                now->count--;
                inum -= now->right ? now->right->count:0;
                now = now->left;
            }
        }
    }
    BTNode* now = root;
    while(true)
    {
        now->count--;
        if(now->num==0)
        {
            now->num = 1;
            break;
        }
        if(now->right and now->right->count>0)
            now = now->right;
        else
            now = now->left;
    }
    vector<int>* ans = new vector<int>(n+1);
    int i = 0;
    BTNode** s = new BTNode*[n+1];
    int top = -1;
    now = root;
    
    while (now!=NULL or top != -1)
    {
        while (now!=NULL)
        {
            s[++top]=now;
            now = now->left;
        }
        if (top!=-1)
        {
            now = s[top];
            (*ans)[i++] = now->num;
            top--;
            now = now->right;
        }
    }
    return ans;
}


vector<int>* getPermutationDecre(vector<int>& interNumber)
{
    vector<int>* ans = new vector<int>(interNumber.size()+1, 1);
    for(int i=interNumber.size()-1; i>=0; i--)
    {
        int num = -1;
        int j;
        for(j=ans->size()-1; j>=0; j--)
            if ((*ans)[j] == 1)
                break;
        
        for(; j>=0; j--)
        {
            if ((*ans)[j] == 1)
                num++;
            else continue;
            if (num == interNumber[i])
            {
                (*ans)[j] = i+2;
                break;
            }
        }
    }
    return ans;
}

vector<int>* getPermutationSJT(vector<int>& interNumber)
{
    vector<int>* ans = new vector<int>(interNumber.size()+1, 1);
    for (int i=interNumber.size()-1; i>=0; i--)
    {
        int dir_var;
        if (i == 0)
        {
            dir_var = 0;
        }
        else if (i%2) //odd
        {
            dir_var = interNumber[i-1];
        }
        else //even
        {
            dir_var = interNumber[i-1]+interNumber[i-2];
        }
        
        if (dir_var%2) //odd
        {
            int num=-1;
            int j;
            for(j=0; j<ans->size(); j++)
                if ((*ans)[j] == 1)
                    break;
            
            for(j=0; j<ans->size(); j++)
            {
                if ((*ans)[j] == 1)
                    num++;
                else continue;
                if (num == interNumber[i]) {
                    (*ans)[j] = i + 2;
                    break;
                }
            }
        }
        else
        {
            int num=-1;
            int j;
            for(j=ans->size()-1; j>=0; j--)
                if ((*ans)[j] == 1)
                    break;
            
            for(; j>=0; j--)
            {
                if ((*ans)[j] == 1)
                    num++;
                else continue;
                if (num == interNumber[i])
                {
                    (*ans)[j] = i+2;
                    break;
                }
            }
        }
    }
    return ans;
}

vector<int>* permutation_Incre(int n,int countNumber)
{
    int count=0;
    vector<int> interNumber(n-1, 0);
    while(true)
    {
        vector<int>* num = getPermutationIncre(interNumber);
        //        for(auto i : *num)
        //        {
        //            cout<<i<<",";
        //        }
        //        cout<<endl;
        if(count==countNumber)
            return num;
        try {
            interNumber = nextIncreInterNumber(interNumber);
        }
        catch (PermutationEndException)
        {
            return num;
        }
        delete num;
        count++;
    }
}

vector<int>* permutation_Incre_Tree(int n,int countNumber)
{
    vector<int> interNumber(n-1, 0);
    int count=0;
    while(true)
    {
        vector<int>* num = getPermutationIncreTree(interNumber);
        //        for(auto i : *num)
        //        {
        //            cout<<i<<",";
        //        }
        //        cout<<endl;
        if(count==countNumber)
            return num;
        try {
            interNumber = nextIncreInterNumber(interNumber);
        }
        catch (PermutationEndException)
        {
            return num;
        }
        delete num;
        count++;
    }
}
void randomInterNumber(vector<int>& interNumber,int n)
{
    for(int i=0;i<interNumber.size();i++)
    {
        interNumber[i]=rand() % (n-1-i);
    }
}
void treeTest(int n,int countNumber)
{
    vector<int> interNumber(n-1,0);
    int count=0;
    while(true)
    {
        if(count==countNumber)
            return;
        randomInterNumber(interNumber, n);
        vector<int>* num=getPermutationIncreTree(interNumber);
        count++;
    }
}
void normalTest(int n,int countNumber)
{
    vector<int> interNumber(n-1,0);
    int count=0;
    while(true)
    {
        if(count==countNumber)
            return;
        randomInterNumber(interNumber, n);
        vector<int>* num=getPermutationIncre(interNumber);
        count++;
    }
}
vector<int>* permutation_Decre(int n)
{
    vector<int> interNumber(n-1, 0);
    while(true)
    {
        vector<int> *num = getPermutationDecre(interNumber);
        //        for(auto i : *num)
        //        {
        //            cout<<i<<",";
        //        }
        //        cout<<endl;
        try {
            interNumber = nextDecreInterNumber(interNumber);
        }
        catch (PermutationEndException)
        {
            return num;
        }
        delete num;
    }
}

vector<int>* permutation_SJT_inter(int n)
{
    vector<int> interNumber(n-1, 0);
    while(true)
    {
        vector<int> *num = getPermutationSJT(interNumber);
        //        for(auto i : *num)
        //        {
        //            cout<<i<<",";
        //        }
        //        cout<<endl;
        try {
            interNumber = nextDecreInterNumber(interNumber);
        }
        catch (PermutationEndException)
        {
            return num;
        }
        delete num;
    }
}

vector<int>* permutation_Dict_inter(int n)
{
    vector<int> interNumber(n-1, 0);
    while(true)
    {
        vector<int> *num = getPermutationDict(interNumber);
        //        for(auto i : *num)
        //        {
        //            cout<<i<<",";
        //        }
        //        cout<<endl;
        try {
            interNumber = nextIncreInterNumber(interNumber);
        }
        catch (PermutationEndException)
        {
            return num;
        }
        delete num;
    }
}





int main()
{
    srand((unsigned)time(NULL));
    int num = 2;
    int size[] = {50,100,1000,10000};
    PMF arrPMF = {
//        permutation_Recur,
//        permutation_Dict,
//        permutation_Dict_inter,
//        permutation_SJT,
//        permutation_SJT_inter,
//        permutation_SJT_improve,
        permutation_Incre,
        permutation_Incre_Tree,
//        permutation_Decre
    };
    const char* a[] = {
//        "permutation_Recur",
//        "permutation_Dict",
//        "permutation_Dict_inter",
//        "permutation_SJT",
//        "permutation_SJT_inter",
//        "permutation_SJT_improve",
        "permutation_Incre",
        "permutation_Incre_Tree",
//        "permutation_Decre"
    };
   /* for (int n: size) {
        printf("N = %d:\n", n);
        for (int i = 0; i < num; i++) {
            double time1 = getTimeStamp();
            vector<int> *last = arrPMF[i](n,1000000);
            double time2 = getTimeStamp();
            printf("Method %s: %.3lf s\n", a[i], time2 - time1);
        }
    }*/
    vector<int> n_permutation={5,10,20,50,100,200,500,1000,2000};
    double time1,time2;
    for(int i=0;i<n_permutation.size();i++)
    {
        time1 = getTimeStamp();
        treeTest(n_permutation[i],10000);
        time2 = getTimeStamp();
        printf("Method TreeVersion %d: %.6lf s\n", i,time2 - time1);
        time1 = getTimeStamp();
        normalTest(n_permutation[i],10000);
        time2 = getTimeStamp();
        printf("Method NormalVersion %d: %.6lf s\n",i, time2 - time1);
    }
    //    vector<int> a{6,7,3,4,2,3,0,0};
    //    vector<int>* ans = getPermutationIncreTree(a);
    //    for(auto i: *ans)
    //    {
    //        cout<<i<<' ';
    //    }
    //    return 0;
}
