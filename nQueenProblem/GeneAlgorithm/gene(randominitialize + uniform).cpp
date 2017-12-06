#include<bits/stdc++.h>
using namespace std;


#define oo 1000007

int n;          //n-queen
int children, GENERATION, POPULATION;
double cross_rate;

struct Data
{

    vector<int> queen;        //queen¦ì¸m
    int attack;             //number of queen attack
    void init()
    {
        queen.clear();
        for(int i = 0 ; i < n ; i++)
            queen.push_back(rand() % n);

        random_shuffle(queen.begin(), queen.end());
        countAttack();
    }
    void countAttack()
    {
        int cnt(0);
        bool check[n + 1];

        memset(check, 0, sizeof(check));
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = i + 1 ; j < n ; j++)
            {
                if(queen[i] == queen[j])
                    cnt++;
                if( abs(queen[i] - queen[j]) == abs(i - j))
                    cnt++;
            }
        }
        attack = cnt;
    }

    bool operator < (Data x) const
    {
        return attack < x.attack;
    }

    void printQueen()const
    {
        cout << "!";
        for(int i = 0 ; i < n ; i++)
            printf("(%d):%d ", i,queen.at(i));
        cout << endl;
    }

};

void initialization(vector<Data>& q)
{
    for(int i = 0 ; i < POPULATION ; i++)
    {
        Data tmp;
        tmp.init();

        q.push_back(tmp);
    }
}

Data cross(const Data& a, const Data& b)
{///O(n)
    Data chi;

    chi.queen.clear();
    for(int i = 0 ; i < n ; i++)
    {
        //random choose the parent's gene
        if(rand() & 1)
            chi.queen.push_back(b.queen[i]);
        else chi.queen.push_back(a.queen[i]);
    }
    return chi;
}

void crossover(vector<Data>& parent)
{///O( n * n * POPULATION * cross_rate)
    long long ch_size = (long long ) POPULATION * cross_rate;

    for(int i = 0 ; i < ch_size ; i++)
    {
        Data tmp, p1, p2;

        for(int j = 0 ; j < 2 ; j++)
        {
            int l = rand() % parent.size();
            int k = rand() % parent.size();
            if(j) p2 = parent[l].attack  < parent[k].attack ? parent[l] : parent[k];
            else p1 = parent[l].attack  < parent[k].attack ? parent[l] : parent[k];
        }


        tmp = cross(p1, p2);
        tmp.countAttack();

        parent.push_back(tmp);
    }


}

void mutation(vector<Data>& child)
{///O(POPULATION * crossrate * n * n)
    for(int i= POPULATION ; i < child.size() ; i++)
    {
        int x, y;
        x = rand() % n;
        y = rand() % n;
        while(y == x) y = rand() % n;

        child[i].queen[x] = y;

        child[i].countAttack();
    }

}


int geneAlgorithm()
{
    int iter(0);
    vector<Data> q;
    initialization(q);
    srand(time(NULL) + rand() % n);
    while(iter < GENERATION)
    {

        //cout << rand() % n << " " << rand() % n << endl;
        vector<Data> children;
        //calculate(q);
        //cp_q = reproduction(q);
        crossover(q);
        mutation(q);
        sort(q.begin(), q.end());


        //cout << q[0].attack << " "<< q[q.size() - 1].attack << endl;
        q.erase(q.begin() + POPULATION, q.end());


        if(q[0].attack == 0)
            break;
        iter++;
    }

    return q[0].attack;
}



int main()
{
    int curAttack, run;
    long double avgAttack(0), avgTime(0), t;
    clock_t t1, t2;
    cin >> n >> POPULATION >> cross_rate >> GENERATION >> run;
    for(int i = 0 ;  i < run ; i++)
    {
        t1 = clock();
        curAttack = geneAlgorithm();
        t2 = clock();
        t = ((long double) t2 - t1) / CLOCKS_PER_SEC;
        avgAttack += curAttack;
        avgTime += t;

        cout << "The " << i + 1 << " run , the number of attack queen is " << curAttack << " in " << t << " seconds.\n";

    }
    system("pause");

    return 0;
}



