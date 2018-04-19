#include<iostream>

using namespace std;

int main()
{
  int m,n;
  int attr,flag=0;
  int l,x,r;
  cout<<"\nEnter the number of attributes: ";
  cin>>n;

  cout<<"\nEnter the number of FDs: ";
  cin>>m;

  int fd[20][20];
  int closure[20][20],tempclosure[20];
  int cl[20],tempcl[20];

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
		}

		cout<<"\nEnter no of RHS attributes: ";
		cin>>r;
		cout<<"\nEnter RHS attributes: ";
		for(int k=0;k<r;k++)
		{
			cin>>x;
			fd[i][x]=-1;
		}

		fd[i][0]=1;
	}

	cout<<"\nFDs are: "<<endl;
	for(int i=0;i<m;i++)
	{
		for(int j=1;j<=n;j++)
			cout<<fd[i][j]<<' ';

		cout<<endl;

	}

  for(int i=0;i<m;i++) // every FD
  {
    for(int j=1;j<=n;j++) // all attributes
    {
      if(fd[i][j]==1)
        {
          attr=j;
          cout<<"\nFD "<<i<<" attr"<<attr<<endl;
          break;
        }
    }

    //compute closure with FD;
    closure[attr][attr]=1;
    cl[attr]=1;

    for(int k=0;k<m;k++) // through every FD
    {
      if(fd[k][attr]==1) // attr present in LHS
      {
        for(int l=1;l<=n;l++)
        {
          if(fd[k][l]==-1)
          {  closure[attr][l]=1;
            cl[l]=1; // add RHS to closure
            for(int x=0;x<m;x++)
            {
              if((fd[x][l]==1)&&(fd[x][0]==1)) //valid FD
              {
                for(int y=1;y<=n;y++)
                {
                    if(fd[x][y]==-1)
                    {  closure[attr][y]=1; cl[y]=1;}
                }
              }
            }
          }
        }
      }

    }

    //ABSENCE OF FD
    tempcl[attr]=1;
    for(int k=0;k<m;k++) // through every FD
    {
      if(k!=i)
      {
      if(fd[k][attr]==1) // attr present in LHS
      {
        for(int l=1;l<=n;l++)
        {
          if(fd[k][l]==-1)
          {  closure[attr][l]=1;
            cl[l]=1; // add RHS to closure
            for(int x=0;x<m;x++)
            {
              if((fd[x][l]==1)&&(fd[x][0]==1)) //valid FD
              {
                for(int y=1;y<=n;y++)
                {
                    if(fd[x][y]==-1)
                    {  closure[attr][y]=1; cl[y]=1;}
                }
              }
            }
          }
        }
      }

    }

    }

    for(int x=1;x<=n;x++)
    {
      if(cl[x]!=tempcl[x])
        flag=1;
    }
    if(flag==1)
    {
          {  fd[i][0]=0; // unnecessary
            cout<<"\nMarked an FD as unnecessary!";
          }
    }

  } // FD necssity checked!
/*
  for(int i=1;i<=n;i++)
  {
      for(int j=1;j<=n;j++)
      {
        if((closure[i][j]==1)&&(i!=j))
        {
          for(int k=1;k<=n;k++)
          {
            if(closure[i][k]!=closure[j][k])
              flag=1;
          }
          if(flag==1)
          {
            //search for the fd
            for(int l=0;l<m;l++)
            {
              if((fd[l][i]==1)&&(fd[l][j]==-1))
              {  fd[l][0]=0; // make it unnecessary
                  cout<<"\nMarked an FD as unnecessary!";
              }
            }
          }
        }
      }
  }
*/
  //Necessary FDs;

  for(int i=0;i<m;i++)
  {
    if(fd[i][0]==1)
    {
      for(int j=1;j<=n;j++)
      {
        cout<<fd[i][j]<<' ';
      }
      cout<<endl;
    }

  }
  cout<<"\nRan successfully!";


  return(0);

}
