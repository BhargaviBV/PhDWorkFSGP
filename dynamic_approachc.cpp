#include<iostream>
#include<fstream>
#include<set>
#include<iterator>
#include<vector>
#include<bits/stdc++.h>
#include<sstream>
#include<boost/algorithm/string.hpp>
#include<time.h>

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
        //cout<<"\t";
        vector <int> hello;
      // op<<"\n";
       // op<<x<<",";
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


int search(string a,int graph)
{


    ifstream fin;
    int flag=0;
    stringstream s;
    s << graph+1;
    string counter;
    counter= s.str();
    string filename="/home/user/Desktop/sem8/programs/connect/skc"+counter+".txt";
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

        return flag;

    }


}

int search1(int a)
{

    ifstream opp;
    opp.open("/home/user/Desktop/sem8/programs/doutput.txt");
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
    cout<<"enter the local minsup threshold\n";
    cin>>minsup;
    cout<<"enter the batch_size\n";
    cin>>batch_size;
   // cout<<"enter the window's size\n";
    //cin>>window_size;
    clock_t start=clock();
    ifstream fin;
    string line;

    string label="";
    int i=0,x=0,y,z,attempt=1;
    int total_graphs=0;

	int isonly=1;
    set <pair<int,int> > edges;

    set <pair<int,int> >::iterator itr;

    
    int count=0,fc;
    string a="",b="",word="";
    int  nsize=graphNum;
	for(int fc=1; fc<=nsize; fc++)
    {
        stringstream s;
        s << fc;
        string counter;
        counter= s.str();
        string filename="/home/user/Desktop/sem8/programs/connect/skc"+counter+".txt";
       // string filename="/home/user/Desktop/sem8/programs/connect/sk"+counter+".txt";
        fin.open(filename.c_str());
	//cout<<"File:"<<filename<<endl;
        while (fin >> word)
        {

            count++;
            if(count%2==1)
                a=word;
            if(count%2==0)
                b=word;
            int x,y;
            x=atoi(a.c_str());
            y=atoi(b.c_str());
            if(x!=0 && y!=0)
            {
                edges.insert(make_pair(x,y));
		//cout<<"Inserted edge:("<<x<<","<<y<<")\n";
                a="";
                b="";
            }

        }
        fin.close();
	    //cout<<"No. of edges:"<<edges.size()<<endl;
    
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
            string finalstring = out_string1 + " " + out_string2;
            x=search(finalstring,graphIndex);
		//cout<<finalstring<<"found status:"<<x<<" edge index:"<<index<<" graph index:"<<graphIndex<<endl;
            dsMatrix[index][graphIndex] = x;
            index++;

        }

    }

    int j;
  /* cout<<"1. DSMatrix:"<<endl;

    for( i=0; i<edges.size(); i++)
    {
        cout<<endl;
        for( j=0; j<graphNum; j++)
        {
           cout<<dsMatrix[i][j]<<" ";
        }
    }*/
//if(isonly==1)return 0;

//------find frequent singleton edges---------------------
/*  
ofstream op;
    op.open("/home/user/Desktop/sem8/programs/doutput.txt");
int relsup=2;
    for( i=0; i<edges.size(); i++)
    {
        int sum = 0;
        for( j=0; j<graphNum; j++)
        {
            sum=sum+dsMatrix[i][j];
        }
        if(sum >= relsup)
        {

            op<<i<<endl;
        }
    }
    op.close();
*/

    map <int, pair <int,int > > history;
    map <int, pair <int,int > > :: iterator h;

    i=0;
    while(i<edges.size())
    {
        history.insert(make_pair(i,make_pair(1,0)));
        i++;
    }

//for(h=history.begin();h!=history.end();h++)
    //  cout<<h->first<<" "<<h->second.first<<" "<<h->second.second<<endl;

    int batch[edges.size()][batch_size];

    for(int i=0; i<edges.size(); i++)
        for(int j=0; j<batch_size; j++)
            batch[i][j]=0;

    	//cout<<"Batches Started here\n";
    //int batch_remove_pointer=0;
   // int total_batches=graphNum/batch_size;
    //cout<<"Total batches= "<<total_batches<<endl;
/*    int k=0;
    while(k<total_batches)
    {
        int e=0;
        int f=0;


        for(int i=0; i<edges.size(); i++)
        {
            e=0;
            for(int j=batch_remove_pointer; j<batch_size+batch_remove_pointer; j++)
            {

                batch[f][e]=dsMatrix[i][j];
                e++;
            }
            f++;
        }
        k++;*/
        //cout<<"\n**********Batch "<<k<<endl;
        //batch_remove_pointer+=batch_size;
        /*
		//y sum is computed? No reason
		int sum=0;

        for(i=0; i<edges.size(); i++)
        {

            for(int j=0; j<batch_size; j++)
            {
                cout<<batch[i][j]<<" ";

            }
            cout<<endl;
        }
        for(i=0; i<edges.size(); i++)
        {
            sum=0;
            int flag=0;
            for(int j=0; j<batch_size; j++)
            {
                sum=sum+batch[i][j];

            }

        }


    }*/


  //*************EDGE COUNT****************/

    int batch1[edges.size()][graphNum];
    int minsup1;

    for(int i=0; i<edges.size(); i++)
        for(int j=0; j<graphNum; j++)
            batch1[i][j]=0;

    //cout<<"234.Batches Started here\n";
    int batch_remove_pointer1=0;
    int total_batches1=graphNum/batch_size;
    //cout<<"Total batches= "<<total_batches1<<endl;
	int  k=0;
    int row=0;
    int col=0;
	ofstream op11;
    op11.open("/home/user/Desktop/sem8/programs/doutput.txt");

    while(k<total_batches1)
    {

        row=0;
        // cout<<"ptr"<<batch_remove_pointer1;
        for(i=0; i<edges.size(); i++)
        {
            col=0;
            for(j=0; j<batch_size+batch_remove_pointer1; j++)
            {

                batch1[row][col]=dsMatrix[i][j];
                col++;
            }
            row++;
        }
        k++;
        //cout<<"\n**********Batch "<<k<<endl;
        //batch_remove_pointer1+=batch_size;
        int sum=0;
	if(k==total_batches1)
	minsup1=minsup;
	else
        minsup1=0.3*(batch_size+batch_remove_pointer1) +1;
        //cout<<"\n";
        //cout<<"relative threshold for "<<k<<" batch(s) is "<<minsup1<<"\n";


        //cout<<"------"<<minsup1;
/*
        for(i=0; i<edges.size(); i++)
        {

            for(j=0; j<batch_size+batch_remove_pointer1; j++)
            {
                cout<<batch1[i][j]<<" ";

            }
            cout<<endl;

        }
        cout<<"\nfrequent edges are :\n";*/
      for(i=0; i<edges.size(); i++)
        {
            sum=0;
            int flag=0;
            for(j=0; j<batch_size+batch_remove_pointer1; j++)
            {
                sum=sum+batch1[i][j];

            }
            h=history.find(i);

            if(sum>=minsup1)
            {
                h->second.second=sum;
                //cout<<i<<" ";
			if(k==total_batches1)
				op11<<i<<endl;
			 
           }
           /* if(sum<minsup1)
            {
                if(k==total_batches)
                {
                    //h->second.first=k+1;
                    h->second.second=sum;
                }
                else
                {
                    h->second.first=h->second.first+1;
                    h->second.second=sum;
                }
            }*/

        }

        //cout<<"\n";
        batch_remove_pointer1+=batch_size;
        if(k==total_batches1)
        {
            batch_remove_pointer1=graphNum-batch_remove_pointer1;
            //cout<<"@@@@@@@@"<<batch_remove_pointer1;
        }
    }

    //cout<<"\n*********Final Edge count\n";
    /*for(h=history.begin(); h!=history.end(); h++)
        cout<<h->first<<" "<<h->second.first<<" "<<h->second.second<<endl;*/

/*cout<<endl<<"frequent edges from edge count";
    op.open("/home/user/Desktop/sem8/programs/output.txt");
    for(h=history.begin(); h!=history.end(); h++)
    {
        if(h->second.second >=minsup1) {
            cout<<h->first<<" ";
            op<<h->first<<endl; }
    }
    op.close();*/

////////////////////////////////////////////////////////////////////////////////////////////////

 ofstream f;
    f.open("/home/user/Desktop/sem8/programs/dneighbour.txt");
    /*------------------- For finding out the neighbours -------------------------*/
   // cout<<"\t----------------Neighbours Information-------------------\n";
    int indexOfFirstItr = 0;
    for(itr=edges.begin(); itr!=edges.end(); ++itr,indexOfFirstItr++)
    {

        //f<<indexOfFirstItr<<" - ";
        set <pair<int,int> >::  iterator itr1;
        int indexOfSecondItr = 0;
        for(itr1=edges.begin(); itr1!=edges.end(); ++itr1, indexOfSecondItr++)
        {
            if((itr->first==itr1->first || itr->first==itr1->second )&& (itr1!=itr))
            {

                f<<indexOfSecondItr<<" ";
            }
            if(itr->second==itr1->first || itr->second==itr1->second && (itr1!=itr) )
            {

                f<<indexOfSecondItr<<" ";
            }
        }
        f<<"\n";
    }
    f.close();


 /********making combinations**/
		//cout<<endl;
//cout<<"frequent combinations are\n";
    int flag[edges.size()];
    for(i=0; i<edges.size(); i++)
        flag[i]=0;
    ifstream fi,gi;
    //string freqfile="/home/user/Desktop/sem8/programs/output.txt";
    fi.open("/home/user/Desktop/sem8/programs/dneighbour.txt");
    string input="";
    k=0;
	int sum=0;
    string filename;
    ofstream opp;
    opp.open("/home/user/Desktop/sem8/programs/doutput1.txt");
    count=0;
    if (fi.is_open())
    {

        while (getline(fi, input))
        {

            int x;
            x=search1(count);
            //cout<<x<<endl;
            if(x==1)
            {
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
//opp.close();


    string line1="";
   
set<string>  fsg;
 //opp.open("/home/user/Desktop/sem8/programs/coutput2.txt");
// op.open("/home/user/Desktop/sem8/programs/coutputf2.txt");
//frequent subgraphs  in coutput2
    fi.open("/home/user/Desktop/sem8/programs/doutput1.txt");
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
                for(j=0; j<graphNum; j++)
                    res[1][j]=res[1][j] & dsMatrix[result1.at(i)][j];


            }

            for(j=0; j<graphNum; j++)
            {

                sum1=sum1+res[1][j];
            }

		string  tmp1="";
            if(sum1>=minsup)
            {
                for(i=0; i<result1.size(); i++)
                {
                   // opp<<result1.at(i)<<" ";
			tmp1+=to_string(result1.at(i))+" ";
			//op<<result1.at(i)<<" ";
                    //cout<<result1.at(i)<<" ";
                }
		//op<<endl;
		//cout<<"is frequent subgraph"<<endl;
		fsg.insert(tmp1);
		//opp<<endl;
                // result1.begin()<<" "<<b<<endl;
            }
            //opp<<",";
        }
        fi.close(); 
	 //  opp.close();//op.close();

    }
 opp.open("/home/user/Desktop/sem8/programs/doutputf.txt");
	for(auto ir:fsg)
	opp<<ir<<endl;
 opp.close();

//*************************************************NEIGHBOURING INFO***************************************/

//cout<<edges.size();
   /* ofstream f;
    f.open("/home/user/Desktop/sem8/programs/neighbour.txt");*/
    /*------------------- For finding out the neighbours -------------------------*/
   // cout<<"\t----------------Neighbours Information-------------------\n";
    /*int indexOfFirstItr = 0;
    for(itr=edges.begin(); itr!=edges.end(); ++itr,indexOfFirstItr++)
    {

        //f<<indexOfFirstItr<<" - ";
        set <pair<int,int> >::	iterator itr1;
        int indexOfSecondItr = 0;
        for(itr1=edges.begin(); itr1!=edges.end(); ++itr1, indexOfSecondItr++)
        {
            if((itr->first==itr1->first || itr->first==itr1->second )&& (itr1!=itr))
            {

                f<<indexOfSecondItr<<" ";
            }
            if(itr->second==itr1->first || itr->second==itr1->second && (itr1!=itr) )
            {

                f<<indexOfSecondItr<<" ";
            }
        }
        f<<"\n";
    }
    f.close();
    -----------------------------------------------------------------------------*/
    clock_t stop=clock();
//cout<<"************************"<<endl;
cout<<"\n"<<"execution time ="<< (((double)(stop-start))/CLOCKS_PER_SEC)<<endl;

    return 0;
}
