// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class Rational
{
  private:
    int ch;
	int zn;
public:
   Rational(void)
   {
	   ch=zn=1;
   }


   Rational(int ch1, int zn1)
   {
	 if(zn1 <= 0)
	  throw "the denominator may not be less than or equal to zero";
	 int a=ch1;
	 int b=zn1;
	 while(a !=0 && b !=0)
		 if(a>b)
		   a=a%b;
		 else
           b=b%a;
	 a=a+b;
     this->ch=ch1/a;
	 this->zn=zn1/a;
   }


   ~Rational(){}
   
   
   void print_rational()
   {
	   cout<<ch<<"/"<<zn;
   }


   Rational & operator+(Rational r)
   {
	  int newch=r.ch*this->zn+this->ch*r.zn;
	  int newzn=this->zn*r.zn;
	  int a=newch;
	  int b=newzn;
	  while(a != 0 && b!=0)
	   if(a>b)
	     a=a%b;
	   else
         b=b%a;
	  a=a+b;
	  this->ch=newch/a;
	  this->zn=newzn/a;
	  return *this;
   }  


   Rational & operator*(Rational r)
   {
	int newch=r.ch*this->ch;
	int newzn=r.zn*this->zn;
	int a=newch;
	int b=newzn;
	while(a != 0 && b!=0)
	 if(a>b)
	   a=a%b;
	 else
       b=b%a;
    a=a+b;
	this->ch=newch/a;
	this->zn=newzn/a;
	 return *this;
   }


   Rational & operator=(Rational r)
   {
	   this->ch=r.ch;
	   this->zn=r.zn;
	   return *this;
   }
};  
template<typename t>
class Matrix
{
private:
  t** r;
  int n;
  int m;
public:
	Matrix()
	{
		this->n=0;
		this->m;
	}


	Matrix(int n1,int m1)
	{
	  if(n1<=0 || m1<=0)
	   throw "matrix can not be a negative number of columns or rows";
	  this->n=n1;
	  this->m=m1;
	  r=new t*[n1];
	  for(int i=0; i<n1; i++)
	    r[i]=new t[m1];
	}


	~Matrix()
	{
		for(int i=0; i<n; i++)
		 delete [] r[i];
		delete [] r;
	}



	t & operator()(int a, int b)
	{
		return this->r[a][b];
	}


	Matrix & operator=(Matrix m)
	{
	   this->r=new t*[m.n];
	   for(int i=0; i<m.n; i++)
	     r[i]=new t[m.m];
	   this->n=m.n;
	   this->m=m.m;
	   for(int i=0; i<this->n; i++)
	    for(int j=0; j<this->m; j++)
		  this->r[i][j]=m.r[i][j];
	   return *this;
	}

	Matrix & operator|(Matrix m)
	{
		if(this->n != m.n)
		  throw "operation can not be performed";

	    Matrix p(this->n, (this->m+m.m));
	    for(int i=0; i<this->n; i++)
		 for(int j=0; j<(this->m+m.m); j++)
		   if(j<this->m)
			  p.r[i][j]=this->r[i][j];
		   else
			  p.r[i][j]=m.r[i][j-this->m];
	    return p;
	}

    Matrix & operator+(Matrix m)
	{
	   if(this->n != m.n || this->m != m.m)
	    throw "operation can not be performed";

	   for(int i=0; i<this->n; i++)
	     for(int j=0; j<this->m; j++)
	       this->r[i][j]=this->r[i][j]+m.r[i][j];
	   return *this;
	}


	Matrix & operator~()
	{
	  Matrix m1(this->m, this->n);
	  for(int i=0; i<this->m; i++)
	    for(int j=0; j<this->n; j++)
	      m1.r[i][j]=this->r[j][i];
	  return m1;
	}
    class iterator
    {
    private:
     Matrix* m;
     int stroka;
	 int stolbec;
    public:
     iterator(Matrix*a, int b, int c)
	 {
		 m=a;
		 stroka=b;
		 stolbec=c;
	 }
	 iterator begin()
	 {
		 return iterator(this, 0, 0);
	 }
	 iterator end()
	 {
		 return iterator(this, m->n, m->m);
	 }
	 bool operator == (iterator i)
	 {
		 if(m == i.m && stroka == i.stroka && stolbec == i.stolbec)
		   return true;
		 else
	       return false;
	 }
	 iterator & operator++()
	 {
		 if(this == this->end())
			 throw "operation can not be performed";
		 if(stolbec != m->m)
		   stolbec++;
		 else
		 {
			 stroka++;
			 stolbec=0;
		 }
		 return this;
	 }
	 t operator*()
	 {
		 return &(m->operator()(stroka, stolbec));
	 }
	};
};
int _tmain(int argc, _TCHAR* argv[])
{
	int a;
	try{
	Matrix<int>m(3,3);
	for(int i=0; i<3; i++)
	 for(int j=0; j<3; j++)
	 {
		 cin>>a;
		 m(i,j)=a;
	 }
	for(int i=0; i<3; i++)
	{
	  for(int j=0; j<3; j++)
	  {
		cout<<m(i,j);
		cout<<"  ";
	  }
	  cout<<endl;
	}
	}
	catch(char* str)
	{
		cout<<str<<endl;
	}
	system("pause");
	return 0;
}

