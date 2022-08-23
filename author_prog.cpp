#include<iostream>
#include<fstream>
#include<set>
#include<iterator>
#include<vector>
#include<bits/stdc++.h>
#include<sstream>
#include<boost/algorithm/string.hpp>
#include<time.h>

//#include<cstdlib>

using namespace std;
int batch_size;
int window_size;
int minsup;
int graphNum=100;



void Combination(vector<int> a, int reqLen, int start, int currLen, bool check[], int len,ofstream& op,int x)
{


    // Return if the currLen is more than the required length.
    if(currLen > reqLen)
        return ;

    // If currLen is equal to required length then print the sequence.
    else if (currLen == reqLen)
    {
        cout<<"\t";
        //op<<endl;
        vector <int> hello;
        //op<<"\n";
        //op<<x<<",";
        for (int i = 0; i < len; i++)
        {

            if (check[i] == true)
            {
                //cout<<a[i]<<",";

                op<<a[i]<<",";
                //hello.push_back(a[i]);
            }


        }
	 op<<"\n";

        //print(hello,reqLen);
        return;
    }
    // If start equals to len then return since no further element left.
    if (start == len)
    {
        return ;
    }
    // For every index we have two options.
    // First is, we select it, means put true in check[] and increment currLen and start.
    check[start] = true;
    Combination(a, reqLen, start + 1, currLen + 1, check, len,op,x);
    // Second is, we don't select it, means put false in check[] and only start incremented.
    check[start] = false;
    Combination(a, reqLen, start + 1, currLen, check, len,op,x);
}

/*void display(int *a,int m,int n)
{
    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<*(a+ i*m + j)<<" ";
        }
        cout<<endl;
    }
} */





int search(string a,int graph)
{


    ifstream fin;
    int flag=0;
    stringstream s;
    s << graph+1;
    string counter;
    counter= s.str();
    string filename="/home/user/Desktop/sem8/programs/connect/skc"+counter+".txt";
    //cout<<filename<<" ";
    fin.open(filename.c_str());
    string line;

    if (fin.is_open())
    {

        while ( getline (fin,line) )
        {

            if(a==line)
            {
                flag=1;

            }
        }
        //fin.close();
        return flag;
        //flag=0;

    }


}

int search1(int a)
{

    ifstream opp;
    opp.open("/home/user/Desktop/sem8/programs/aoutput.txt");
    string line="";
    stringstream s;
    s << a;
    string counter;
    counter= s.str();
    while(opp>>line)
    {
        if(counter==line)
            return 1;
    }
    return 0;

}

int main()
{
    cout<<"enter the minsup threshold\n";
    cin>>minsup;
    cout<<"enter the batch_size\n";
    cin>>batch_size;
    cout<<"enter the window's size\n";
    cin>>window_size;
    clock_t start=clock();
    ifstream fin;
    string line;

    string label="";
    int i=0,x=0,y,z,attempt=1;
    int total_graphs=graphNum;


    set <pair<int,int> > edges;
    //set <pair<string,string> > edges1;

    set <pair<int,int> >::	iterator itr;//;::edges<int[2]>;

    
	int whole_graphs[6][total_graphs];
    int count=0,fc;
    string a="",b="",word="";
    for(int fc=1; fc<=graphNum; fc++)
    {
        stringstream s;
        s << fc;
        string counter;
        counter= s.str();
        string filename="/home/user/Desktop/sem8/programs/connect/skc"+counter+".txt";
        //cout<<filename;
        fin.open(filename.c_str());
        //cout<<fc<<endl;
        while (fin >> word)
        {

            count++;
            //cout<<word;
            if(count%2==1)
                a=word;
            if(count%2==0)
                b=word;
            //string l="";
            int x,y;
            x=atoi(a.c_str());
            y=atoi(b.c_str());
            if(x!=0 && y!=0)
            {
                //cout<<x<<" "<<y<<endl;
                edges.insert(make_pair(x,y));
                //cout<<"hello";

                a="";
                b="";
            }

        }
//cout<<fc<<endl;
        fin.close();
    }


//*************************************************dsmatrix***************************************/

    int dsMatrix[edges.size()][graphNum];
    for(int m=0; m<edges.size(); m++)
    {
        for(int n=0; n<graphNum; n++)
        {
            dsMatrix[m][n]=0;
        }
    }
    int index=0,graphIndex;
    set < pair<int,int> > :: iterator iter;
    for( graphIndex = 0; graphIndex < graphNum; ++graphIndex)
    {
        //------Calclate dsMatrix
        index=0;
        for(iter = edges.begin(); iter!=edges.end(); ++iter)
        {
            int first = iter->first;
            int second = iter->second;

            string out_string1,out_string2;
            stringstream ss,ss1;
            ss << first;
            ss1 << second;
            out_string1 = ss.str();
            out_string2 = ss1.str();
            //cout<<out_string2;
            string finalstring = out_string1 + " " + out_string2;
            //cout<<finalstring<<" ";
            //define graphNum
            //cout<<"hel";

            x=search(finalstring,graphIndex);
            //cout<<"*****"<<endl;
            //cout<<x;


            //make search funct ion

            dsMatrix[index][graphIndex] = x;
            //cout<<index<<" "<<graphIndex<<" ";
            //  cout<<" "<<dsMatrix[index][graphIndex]<<endl;
            index++;




        }

    }

    int j;
/*cout<<"1.DSMatrix"<<endl;

    for( i=0; i<edges.size(); i++)
    {
        cout<<endl;
        for( j=0; j<graphNum; j++)
        {
            cout<<dsMatrix[i][j]<<" ";
        }
    }
*/
    int batch[edges.size()][graphNum];

    for(int i=0; i<edges.size(); i++)
        for(int j=0; j<graphNum; j++)
            batch[i][j]=0;

    //cout<<"Batches Started here\n";
    int batch_remove_pointer=0;
    int total_batches=graphNum/batch_size;
    //cout<<"Total batches= "<<total_batches<<endl;
    int k=0,e=0,row=0;
    while(k<(total_batches-1))
    {
       // int row=0;

        for(i=0;i<edges.size();i++)
        {
            //e=0;
            for(int j=batch_remove_pointer; j<(batch_size*window_size)+batch_remove_pointer; j++)
            {
                batch[i][j]=dsMatrix[i][j];
                //e++;
            }
            //row++;
        }
	//cout<<batch_size<<window_size;


      // cout<<endl;
	/*cout<<"\nsliding window "<<k+1<<endl;

        for( i=0; i<edges.size(); i++)
        {
            for( j=batch_remove_pointer; j<(batch_size*window_size)+batch_remove_pointer; j++)
            {
                cout<<batch[i][j]<<" ";
            }
            cout<<endl;
        }*/


	 k++;

        if(k==(total_batches-1))
        {
            ofstream op;
            op.open("/home/user/Desktop/sem8/programs/aoutput.txt");

            //------find frequent edges

            for( i=0; i<edges.size(); i++)
            {
                int sum = 0;
                for( j=batch_remove_pointer; j<(batch_size*window_size)+batch_remove_pointer; j++)
                {
                    sum=sum+batch[i][j];
                }
                if(sum >= minsup)
                {

                    op<<i<<endl;
                }
            }
            op.close();
        }

	 batch_remove_pointer+=batch_size;


        //cout<<"\n Next Batch\n";
    }



    // cout<<"Sliding Window\n";
/*************************************************NEIGHBOURING INFO***************************************/

//cout<<edges.size();
    ofstream f;//,g;
    f.open("/home/user/Desktop/sem8/programs/aneighbour.txt");
  // g.open("/home/user/Desktop/sem8/programs/aneighbour1.txt");
    /*------------------- For finding out the neighbours -------------------------*/
   // cout<<"\t----------------Neighbours Information-------------------\n";
    int indexOfFirstItr = 0;
    for(itr=edges.begin(); itr!=edges.end(); ++itr,indexOfFirstItr++)
    {
        //g<<indexOfFirstItr<<" - ";
        set <pair<int,int> >::  iterator itr1;
        int indexOfSecondItr = 0;
        for(itr1=edges.begin(); itr1!=edges.end(); ++itr1, indexOfSecondItr++)
        {
            if((itr->first==itr1->first || itr->first==itr1->second )&& (itr1!=itr))
            {

                f<<indexOfSecondItr<<" ";
               // g<<indexOfSecondItr<<" ";
            }
            if(itr->second==itr1->first || itr->second==itr1->second && (itr1!=itr) )
            {

                f<<indexOfSecondItr<<" ";
                //g<<indexOfSecondItr<<" ";
            }
        }
        f<<"\n";
     //   g<<"\n";
    }
    f.close();
   // g.close();

    /*int flag[edges.size()];
    for(i=0; i<edges.size(); i++)
        flag[i]=0;
    ifstream fi,gi;
    string freqfile="/home/user/Desktop/sem8/programs/aoutput.txt";
    string neighbour="/home/user/Desktop/sem8/programs/aneighbour.txt";
    vector <int> v;
    fi.open(freqfile.c_str());
    while(fi>>word)
    {
        int a=atoi(word.c_str());
        v.push_back(a);
        flag[a]=1;
    }
    fi.close();
*/
    //for(i=0; i<edges.size(); i++)
// cout<<flag[i];
    //vector<int> :: iterator vit;
    //for(vit=v.begin();vit!=v.end();vit++)
    //	cout<<*vit<<" ";


	ifstream fi;

    fi.open("/home/user/Desktop/sem8/programs/aneighbour.txt");
    string input="";
    int sum=0;
    string filename;
    ofstream opp;
    opp.open("/home/user/Desktop/sem8/programs/aoutput1.txt");
    count=0;
//opp.open("/home/user/Desktop/sem8/programs/output1.txt");
    if (fi.is_open())
    {

        while (getline(fi, input))
        {
            // using printf() in all tests for consistency


            int x;
            x=search1(count);
            //cout<<x<<endl;
            if(x==1)
            {


//cout<<count;
                vector<string> result;
                boost::split(result, input, boost::is_any_of(" "));
                vector <int> result1 ;
                vector <int> :: iterator rs;
                vector<string> :: iterator st;
                //for(st=result.begin();st!=result.end();st++)
                //cout<<*st<<" ";

                for (int i = 0; i < result.size()-1; i++)
                {
                    int o;
                    o=atoi((result.at(i)).c_str());
                    result1.push_back(o);
                }
                bool check[result1.size()];
                for(i = 0; i < result1.size(); i++)
                {

                    check[i] = false;
                }
                //cout<<"****************"<<result1.size()<<endl;

                for(i=0; i<result1.size(); i++)
                {
                    int x;
                    x=search1(result1.at(i));
                    //cout<<x<<endl;
                    if(x==0)
                    {
                        //cout<<	*(result1.begin()+i)<<" ";
                        result1.erase(result1.begin()+i);
			//i--;
                    }

                }
                /*for(rs=result1.begin();rs!=result1.end();rs++)
                	{
                		cout<<*rs;
                	}*/

                for(i = 1; i <=result1.size(); i++)
                {
                    //opp<<count;
                    Combination(result1, i, 0, 0, check,result1.size(),opp,count);

                }
            }

            count++;

            // opp<<"\n";

        }

        opp.close();
        fi.close();
    }
    opp.close();

//ds(dsMatrix);



set<string>  fsg;
    string line1="";
    //opp.open("/home/user/Desktop/sem8/programs/aoutput2.txt");
    fi.open("/home/user/Desktop/sem8/programs/aoutput1.txt");
	//cout<<"\nBefore:brp:"<<batch_remove_pointer;
	batch_remove_pointer+=batch_size;

	batch_remove_pointer=batch_remove_pointer-(window_size*batch_size);
	//cout<<"\n after brp:"<<batch_remove_pointer;

    if (fi.is_open())
    {

        while (getline(fi, line1))
        {
            //cout<<line1<<endl;
            vector<string> result;
            boost::split(result, line1, boost::is_any_of(","));
            vector <int> result1 ;
            vector <int> :: iterator rs;
            vector<string> :: iterator st;

            for (int i = 0; i < result.size()-1; i++)
            {
                int o;
                o=atoi((result.at(i)).c_str());
                result1.push_back(o);
            }
            //cout<<endl;
            //for(rs=result1.begin();rs!=result1.end();rs++)
            //cout<<*rs<<" ";

            int res[1][graphNum];
            int j=0,sum1=0;
            for(j=0; j<graphNum; j++)
                res[1][j]=1;
            j=0;

            for(i=0; i<result1.size(); i++)
            {
                for(j=batch_remove_pointer; j<graphNum; j++)
                    res[1][j]=res[1][j] & batch[result1.at(i)][j];


            }

            for(j=batch_remove_pointer; j<graphNum; j++)
            {
                //cout<<res[1][j];
                sum1=sum1+res[1][j];
            }
            //cout<<"******";
		string  tmp1="";
            if(sum1>=minsup)
            {
                for(i=0; i<result1.size(); i++)
                {
			tmp1+=to_string(result1.at(i))+" ";
                    //opp<<result1.at(i)<<" ";
                   // cout<<result1.at(i)<<" ";
                }
		fsg.insert(tmp1);
                // result1.begin()<<" "<<b<<endl;
            }
            //opp<<"\n";
        }
        fi.close();
    }
    //opp.close();

 opp.open("/home/user/Desktop/sem8/programs/aoutputf.txt");
	for(auto ir:fsg)
	opp<<ir<<endl;
 opp.close();

    // for(i=0; i<graphNum; i++)
    //   cout<<res[1][i];

//////////////////////for sliding windows  /////////////////////////////////
    /*====================================== Making Batches from whole Graph Matrix ==========================*/

    /*  int batch[6][batch_size*window_size];

      for(int i=0;i<6;i++)
          for(int j=0;j<batch_size*window_size;j++)
          batch[i][j]=0;

        cout<<"Batches Started here\n";
      int batch_remove_pointer=0;
    int total_batches=graphNum/batch_size-1;
    //cout<<"Total batches= "<<total_batches<<endl;
      int k=0;
      while(k<total_batches){
             int e=0;
             int f=0;

         for(int j=batch_remove_pointer;j<(batch_size*window_size)+batch_remove_pointer;j++){
                  f=0;
                  for(int i=0;i<6;i++){
          batch[f][e]=dsMatrix[i][j];
          f++;
          }
          e++;
      }
          k++;
          batch_remove_pointer+=batch_size;
          display(batch[0],6,(batch_size*window_size));
          cout<<"\n Next Batch\n";
      }
    */
//set <pair<int,int> >::	iterator itr1;
//for(itr1=edges.begin(); itr1!=edges.end(); ++itr1)
//cout<<itr1->first<<" "<<itr1->second<<endl;

////////////////////////////////////////////////////////////////////////////////////////////////




    /*-------------------------------------------------------------------------------------*/
clock_t stop=clock();
//cout<<"************************"<<endl;
cout<<"\n"<<"execution time ="<< (double)(stop-start)/CLOCKS_PER_SEC<<"seconds"<<endl;

    return 0;
}
