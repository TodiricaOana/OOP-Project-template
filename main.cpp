#include <iostream>
#include <new>
#include <cstring>
#include <cstdlib>
#include<stdexcept>
using namespace std;

template <class T> class Vector;
template <class T> istream &operator >>(istream &in, Vector <T> &V);
template <class T> class Vector;
template <class T> ostream &operator <<(ostream &out, const Vector <T> &V);



template <class T>
class Vector
{
    T *v;
    int n;

public:

    class iterator
    {
        T * element;
    public:
        iterator(T * el) : element(el) {};
        iterator():element(NULL){};

        const iterator &operator ++ ()
        {
            element++;
            return *this;
        }
        const iterator operator ++ (int i)
        {
            iterator aux;
            aux.element=element;
            element++;
            return aux;
        }
        T& operator * ()const
        {
            return *element;
        }

        T *operator -> ()const
        {
            return element;
        }

        bool operator == (const iterator &el)const
        {
           if(element ==el.element)
                return true;
            else
                return false;
        }
        bool operator != ( const iterator &el)const
        {
            if(element==el.element)
                return false;
            else
                return true;

        }
        ~iterator() {}

    };

    Vector(): n(0) {v=NULL;}

    Vector(int i, T x);

    ~Vector();

    Vector(const Vector<T> &V);

    friend ostream & operator<< <> (ostream &in,const Vector <T> &V);
    friend istream & operator >> <> (istream &out, Vector<T> &V);
    Vector<T> & operator = (const Vector <T> &V);
    void Push_back (const T & x);
    void Push_back(const char * const&x);
    void Pop_back ();
    void Insert ( const T & x , int i);
    void Insert (const char * const &x, int i);
    void  Remove (int i);

    operator int()
    {
        return n;
    }
     operator bool() const
    {
        if((*this)!=0)return true;
        else
            return false;
    }

   T & operator[](int i);


    // orice clasa care implementeaza iteratori are o metoda begin, care intoarce un iterator la primul element
    iterator begin() { return iterator(v); }

    // si o metoda end, care intoarce un iterator catre elementul de dupa ultimul element
    iterator end() { return iterator(v+n); }


};

template<class T> Vector<T>:: ~Vector()
{

    delete []v;
    n=0;
}
template<> Vector<char*>:: ~Vector()
{
  for(int i=0;i<n;i++)
      delete []v[i];
    delete []v;
    n=0;
}

template <class T> ostream & operator<<(ostream &out,const Vector<T> &V)
{
    for(int i=0;i<V.n;i++)
        out<<V.v[i]<<"   ";
    return out;
}

template <class T> istream & operator >>  (istream &in, Vector<T> & V)
{
    delete[] V.v;
    int n;
    in>>n;

    V.v= new T[V.n+1];
    T x;
    for(int i=0; i<n; i++)
        {   in>>x;
            V.Push_back(x);
        }
    return in;
}

template<class T>Vector<T>::Vector(int i, T x)
    {

        if(i <= 0)
            throw 0;

        v= new T[i+1];

        for(int j=0;j<i;j++)
            Push_back(x);

    }

template<class T> Vector<T>::Vector(const Vector <T> &V)
{
    n=0;

    v= new T[V.n+1];

    for(int i=0;i<V.n;i++)
         Push_back(V.v[i]);

}

template<class T> Vector<T> & Vector<T>::operator=(const Vector<T>& V)
{
    if(this==&V) return *this;

    delete[] v;
    n=0;

    v= new T[V.n+1];

    for (int i=0; i<V.n; i++)
        Push_back(V.v[i]);
    return *this;
}

template<class T> void Vector<T>::Push_back(const T &x)
{
    T *w;

    w=new T[n+2];

    for(int i=0;i<n;i++)
    {
        w[i]=v[i];

    }
        delete []v;
       v=w;
       v[n]=x;
       n++;

}


template<> void Vector<char *>::Push_back( char *const &x)
{

    char **w;

    w=new char *[n+2];

    for(int i=0;i<n;i++)
    {
        w[i]=new char[strlen(v[i]+1)];
        strcpy(w[i],v[i]);

    }
     for(int i=0;i<n;i++)
        delete []v[i];
    delete []v;

       v=w;
       v[n]=new char[strlen(x)+1];
       strcpy(v[n],x);
       n++;


}

template<> void Vector<char *>::Push_back(const char *const &x)
{

    char **w;

    w=new char *[n+2];


    for(int i=0;i<n;i++)
    {
        w[i]=new char[strlen(v[i]+1)];
        strcpy(w[i],v[i]);

    }
     for(int i=0;i<n;i++)
        delete []v[i];
    delete []v;

       v=w;
       v[n]=new char[strlen(x)+1];
       strcpy(v[n],x);
       n++;


}

template<class T> void Vector<T>::Pop_back()
{
    n--;
    delete v[n];

}

template<class T> void Vector<T>::Insert(const T &x, int i)
{
    T *w;

    w=new T[n+2];

    for(int j=0;j<n;j++)
        w[j]=v[j];

       delete []v;
       v=w;
       for(int j=n-1;j>=i;j--)
            v[j+1]=v[j];
       v[i]=x;
       n++;

}

template<> void Vector<char *>::Insert(char * const &x, int i)
{
    char **w;

    w=new char *[n+2];

    for(int j=0;j<n;j++)
       {
        w[j]=new char[strlen(v[j]+1)];
        strcpy(w[j],v[j]);
       }

    for(int i=0;i<n;i++)
            delete []v[i];
       delete []v;
       v=w;
       for(int j=n-1;j>=i;j--)
            strcpy(v[j+1],v[j]);
       strcpy(v[i],x);
       n++;
}

template<> void Vector<char *>::Insert(const char * const &x, int i)
{
    char **w;

    w=new char *[n+2];

    for(int j=0;j<n;j++)
       {
        w[j]=new char[strlen(v[j]+1)];
        strcpy(w[j],v[j]);
       }
    for(int i=0;i<n;i++)
        delete []v[i];
       delete []v;
       v=w;
       for(int j=n-1;j>=i;j--)
            strcpy(v[j+1],v[j]);
       strcpy(v[i],x);
       n++;
}

template<class T> void Vector<T>::Remove(int i)
{
    T *w;

    w=new T[n+2];

    int m=0;
    for(int j=0;j<n;j++)
        if(j!=i)
        w[m++]=v[j];

          n--;

     delete []v;
     v=w;

}

template<> void Vector<char *>::Remove(int i)
{
    char **w;

    w=new char *[n+2];

    int m=0;
    for(int j=0;j<n;j++)
        if(j!=i)
        w[m++]=v[j];

          n--;

    for(int j=0;j<=n;j++)
        delete []v[i];
     delete []v;
     v=w;


}
template<class T> T & Vector<T> ::operator[](int i)
{

       if(i < 0 || i >= n)
        throw 0;

    return v[i];
}


int main()
{

    /* Vector <int> v(5,3);
    Vector <int> w;
    if(!w)cout<<"nu";
    w=v;
    int x=4;
    w.Push_back(6);

    w.Insert(x,2);
    w.Remove(3);
    w[4]=2;

    cout<<int(w)<<" ";

    cout<<w;
 */
    Vector <char*> v;
    v.Push_back("Ana");
    v.Push_back("are");
    v.Push_back("mere");
    cout<<v<<endl;

    Vector <char*> w(4, "ANA");
    w=v;
    strcpy(w[1],"n-are");
    strcpy(w[0],"Maria");



   for(typename Vector<char *>::iterator i=w.begin(); i!=w.end();i++)
      cout<<*i<<"  ";


    return 0;
}
