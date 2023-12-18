#include<bits/stdc++.h>
using namespace std;
class knapsack{
	public:
		int knapsack_greedy(vector<pair<int,pair<int,int>>> V,int n,int capacity){
			
			float ratio[n];
			for(int i=0;i<n;i++)
			{
				ratio[i]=V[i].second.first/ (float)V[i].second.second;
			}
			float temp;
			pair<int,pair<int,int>>temp2;
			for(int i=0;i<n;i++)
			{
				for(int j=i+1;j<n;j++)
				{
					if(ratio[i]>ratio[j])
					{
						temp=ratio[i];
						ratio[i]=ratio[j];
						ratio[j]=temp;
						
						temp2=V[i];
						V[i]=V[j];
						V[j]=temp2;
						
					}
				}
				
			}
			for(int i=0;i<n;i++)
			{
				cout<<V[i].first<<"  "<<V[i].second.first<<"   "<<V[i].second.second<<endl;
			}
			
			int remw=capacity;
			int profit=0;
			for(int i=n-1;i>=0;i--)
			{
				if(remw<=V[i].second.second)
				{
					profit+=V[i].second.first;
					remw-=V[i].second.second;
				}
				else{
					profit+=((remw/(float)V[i].second.second)*V[i].second.first);
					remw=0;
					break;
				}
			}
			return profit;
		}
		
};
int main()
{
	int n;
	cin>>n;
	int capacity;
	cin>>capacity;
	vector<pair<int,pair<int,int>>> V;
	for(int i=0;i<n;i++)
	{
		int profit,weight;
		cin>>profit>>weight;
		V.push_back({i+1,{profit,weight}});
		
	}
	knapsack k;
	int p=k.knapsack_greedy(V,n,capacity);
	cout<<p;
	
	
}