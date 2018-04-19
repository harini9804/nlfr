#include<iostream>

using namespace std;

int same(int tempcl[20], int cl[20], int n);
void print(int arr[20],int n);
int same(int tempcl[20], int cl[20], int n);
void copy(int tempcl[20],int cl[20], int n);

int count(int arr[20],int n, int x)
{
  int cnt=0;
  for(int i=1;i<=n;i++)
  {
    if(arr[i]==x)
      cnt++;
  }

  return(cnt);
}

void print(int arr[20],int n)
{
  for(int i=1;i<=n;i++)
  {
    cout<<' '<<arr[i]<<' ';
  }
  cout<<endl;
}
int same(int tempcl[20], int cl[20], int n)

{
  for(int i=1;i<=n;i++)
  {
    if(tempcl[i]!=cl[i])
    return(0);
  }

  return(1);

}
void copy(int tempcl[20],int cl[20], int n)
{
  for(int i=1;i<=n;i++)
  {
    tempcl[i]=cl[i];
  }
}
int subset(int lhs[20], int cl[20],int n)
{
  for(int i=1;i<=n;i++)
  {
    if((lhs[i]==1)&&(lhs[i]!=cl[i]))
      return(0);
  }

  return(1);
}
void initialise(int arr[20],int n)
{
  for(int i=1;i<=n;i++)
    arr[i]=0;
}
void addrhs(int rhs[20], int cl[20], int n)
{
  for(int i=1;i<=n;i++)
  {
    if(rhs[i]==-1)
    {
      cl[i]=1;
    }
  }
}
void addlhs(int lhs[20], int cl[20], int n)
{
  for(int i=1;i<=n;i++)
  {
    if(lhs[i]==1)
    {
      cl[i]=1;
    }
  }
}


int main()
{
  int m,n;
  int flag=0;
  int l,x,r;
  cout<<"\nEnter the number of attributes: ";
  cin>>n;

  cout<<"\nEnter the number of FDs: ";
  cin>>m;

  int fd[20][20];
  int lhs[20],rhs[20];
  int cl[20],tempcl[20],clwo[20],rel[20],attr[20];

  //-----initialise--
  initialise(lhs,n);
  initialise(rhs,n);
  initialise(cl,n);
  initialise(tempcl,n);
  initialise(clwo,n);
  initialise(rel,n);
  initialise(attr,n);

  for(int i=1;i<=n;i++)
    rel[i]=1;

  for(int i=0;i<m;i++)
	{
		cout<<"\nEnter FD "<<i+1<<": ";
		for(int j=1;j<=n;j++)
			fd[i][j]=0;
		cout<<"\nEnter no of LHS attributes: ";
		cin>>l;
		cout<<"\nEnter LHS attributes: ";
		for(int k=0;k<l;k++)
		{
			cin>>x;
			fd[i][x]=1;
      lhs[x]=1;
		}

		cout<<"\nEnter no of RHS attributes: ";
		cin>>r;
    m=m+r-1;
		cout<<"\nEnter RHS attributes: ";

			cin>>x;
			fd[i][x]=-1;
    for(int k=0;k<r-1;k++)
  	{
      i++;
      copy(fd[i],lhs,n);
      cin>>x;
      fd[i][x]=-1;
      fd[i][0]=1;


		}

		fd[i][0]=1;
	}

  // Splitting RHS done.



	cout<<"\nFDs are: "<<endl;
	for(int i=0;i<m;i++)
	{
		for(int j=1;j<=n;j++)
			cout<<fd[i][j]<<' ';

		cout<<endl;

	}

  for(int i=0;i<m;i++) // every FD
  {
    initialise(cl,n);

    for(int j=1;j<=n;j++)
    {
      if(fd[i][j]==1)
      {
        cl[j]=1; // Added to closure set
      }
    }
    cout<<"\nLHS of FD "<<i<<" :";
    print(cl,n);
    copy(attr,cl,n);
    while(!same(tempcl,cl,n))
    {
      copy(tempcl,cl,n);
      for(int i=0;i<m;i++)
      {
        initialise(lhs,n);
        initialise(rhs,n);
        for(int j=1;j<=n;j++)
        {
          if(fd[i][j]==1)
            lhs[j]=1;
          if(fd[i][j]==-1)
            rhs[j]=-1;
        } // got lhs of FD
        if(subset(lhs,cl,n))
        {  addrhs(rhs,cl,n);
          cout<<"\nAdded rhs from FD "<<i<<" .\n";
        }
        if(same(cl,rel,n))
          break;

      }
      if(same(cl,rel,n))
        break;

    }

    cout<<"\nClosure of FD "<<i<<" is: ";
    print(cl,n);

    initialise(clwo,n);
    copy(clwo,attr,n); //copies attr to clwo;

    cout<<"\nFinding closure of ";
    print(clwo,n);
    cout<<"without the FD: ";
    initialise(tempcl,n);
    while(!same(tempcl,clwo,n))
    {
      copy(tempcl,clwo,n);
      for(int x=0;x<m;x++)
      {
        initialise(lhs,n);
        initialise(rhs,n);
        if(x==i)
          continue; // skip that fd;
        for(int j=1;j<=n;j++)
        {
          if(fd[x][j]==1)
            lhs[j]=1;
          if(fd[x][j]==-1)
            rhs[j]=-1;
        } // got lhs of FD
        cout<<"\nlhs of fd"<<x<<" :";
        print(lhs,n);
        cout<<"\nclwo"<<x<<" :";
        print(clwo,n);
        if(subset(lhs,clwo,n))
        {  addrhs(rhs,clwo,n);
          cout<<"\nAdded rhs from FD "<<x<<" .\n";
        }
        if(same(clwo,rel,n))
          break;

      }
      if(same(clwo,rel,n))
        break;

    }

    cout<<"\nCLOSURE: ";
    print(clwo,n);
    if(same(cl,clwo,n))
    {
      cout<<"\nFD "<<i<<" is redundant!";
      fd[i][0]=0;
    }




  }

cout<<"\nFDs required are: ";

for(int i=0;i<m;i++)
{
  if(fd[i][0]==1)
    print(fd[i],n);
}


cout<<"\nFinished!";
  return(0);

}
