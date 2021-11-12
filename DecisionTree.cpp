#include<bits/stdc++.h>
using namespace std;

//Info about each row
struct info{
	string age;
	string income;
	string student;
	string credit;
	string isBuy;
};

//Tree Node
typedef struct node{
	string splitClass;
	vector<string> value;
	vector<info> v;
	vector<node *> child;
	vector<string> attrList;
	string final;
}*PTR;

vector<info> information;

//Get the entire Data in a vector
void getDataSet(fstream &fin,PTR &T){
	string s1,s2,s3,s4,s5,s6;
	fin>>s1>>s2>>s3>>s4>>s5>>s6;
	T->attrList.push_back("age");
	T->attrList.push_back("income");
	T->attrList.push_back("student");
	T->attrList.push_back("credit");
	T->attrList.push_back("isBuy");
	while(!fin.eof()){
		info i;
		fin>>s1>>s2>>s3>>s4>>s5>>s6;
		i.age=s2;
		i.income=s3;
		i.student=s4;
		i.credit=s5;
		i.isBuy=s6;
		information.push_back(i);
	}
}

//To see whether all the samples are in the same class
bool isSameClass(vector<info> &v){
	int yes=0,no=0;
	for(int i=0;i<v.size();i++){
		if(v[i].isBuy=="no") no++;
		else yes++;
	}
	if(yes==v.size() || no==v.size()) return true;
	else false;
}

float helper(map<pair<string,string>,int> &m,int total){
		
		map<pair<string,string>,int>::iterator it1,it2;
		map<string,int> mp;
		mp.clear();
		float result=0,yes,no,totaltmp;
		for(it1=m.begin();it1!=m.end();it1++){
		yes=0;no=0;
		if(mp.find(it1->first.first)==mp.end()){
			mp[it1->first.first]=0;
		for(it2=m.begin();it2!=m.end();it2++){
					   if(it2->first.first==it1->first.first && it2->first.second=="no") no=it2->second;
					   else if(it2->first.first==it1->first.first) yes=it2->second;
					}
			totaltmp=yes+no;
			float x,y,z;
			x=-1*(totaltmp/total);
			y=(yes/totaltmp)*log2(yes/totaltmp);
			z=(no/totaltmp)*log2(no/totaltmp);
			if(x*(y+z)>0){
				result+=x*(y+z);
			}
			}
	}
	return result;
}
//To select The best Attribute
string AttributeSelection(vector<info> &v,vector<string> &attrList){
	map<pair<string,string>,int> age,income,student,credit;
	float yes=0,no=0,total,totaltmp,info,ans=INT_MIN,infoage=0,infoincome=0,infostudent=0,infocredit=0;
	string result="";
	map<string,int> mp;
	for(int i=0;i<attrList.size()-1;i++){
		mp[attrList[i]]=0;
		for(int j=0;j<v.size();j++){
			if(attrList[i]=="age"){
				if(age.find(make_pair(v[j].age,v[j].isBuy))==age.end()){
					age[make_pair(v[j].age,v[j].isBuy)]=1;
				}
				else age[make_pair(v[j].age,v[j].isBuy)]++;
			}
			else if(attrList[i]=="income"){
			   if(income.find(make_pair(v[j].income,v[j].isBuy))==income.end()){
					income[make_pair(v[j].income,v[j].isBuy)]=1;
				}
				else income[make_pair(v[j].income,v[j].isBuy)]++;
			}
			else if(attrList[i]=="student"){
				if(student.find(make_pair(v[j].student,v[j].isBuy))==student.end()){
					student[make_pair(v[j].student,v[j].isBuy)]=1;
				}
				else student[make_pair(v[j].student,v[j].isBuy)]++;
			}
			else if(attrList[i]=="credit"){
				if(credit.find(make_pair(v[j].credit,v[j].isBuy))==credit.end()){
					credit[make_pair(v[j].credit,v[j].isBuy)]=1;
				}
				else credit[make_pair(v[j].credit,v[j].isBuy)]++;
			}
		}
	}
	for(int i=0;i<v.size();i++){
		if(v[i].isBuy=="yes") yes++;
		else no++;
	}
	total=yes+no;
	//Calculating the total info
	info=-1*((yes/total)*log2(yes/total)+(no/total)*log2(no/total));
	//Calculating individual info
	infoage=info-helper(age,total);
	infoincome=info-helper(income,total);
	infostudent=info-helper(student,total);
	infocredit=info-helper(credit,total);
	
	//cout<<infoage<<" "<<infoincome<<" "<<infostudent<<" "<<infocredit<<endl;
	
	if(infoage>ans && mp.find("age")!=mp.end()){
		ans=infoage;
		result="age";
	}
	
	if(infoincome>ans && mp.find("income")!=mp.end()){
		ans=infoincome;
		result="income";
	}
	
	if(infostudent>ans && mp.find("student")!=mp.end()){
		ans=infostudent;
		result="student";
	}
	
	if(infocredit>ans && mp.find("credit")!=mp.end()){
		ans=infocredit;
		result="credit";
	}
	
	return result;
	
}
//To send all The unique values of a particular attribute
vector<string> getUnique(string attr,vector<info> &v){
	vector<string> result;
	map<string,int> mp;
	for(int i=0;i<v.size();i++){
		if(attr=="age"){
			if(mp.find(v[i].age)==mp.end()){
				mp[v[i].age]=0;
				result.push_back(v[i].age);
			}
		}
		
		if(attr=="income"){
			if(mp.find(v[i].income)==mp.end()){
				mp[v[i].income]=0;
				result.push_back(v[i].income);
			}
		}
		
		if(attr=="student"){
			if(mp.find(v[i].student)==mp.end()){
				mp[v[i].student]=0;
				result.push_back(v[i].student);
			}
		}
		
		if(attr=="credit"){
			if(mp.find(v[i].credit)==mp.end()){
				mp[v[i].credit]=0;
				result.push_back(v[i].credit);
			}
		}
	}
	return result;
	
}
//To send the vector of info for a particular node
vector<info> getVector(string attr,string value,vector<info> &v){
	vector<info> result;
	for(int i=0;i<v.size();i++){
		if(attr=="age" && v[i].age==value){
			info in;
			in.age=v[i].age;in.credit=v[i].credit;in.income=v[i].income;in.student=v[i].student;in.isBuy=v[i].isBuy;
			result.push_back(in);
		}
		
		
		if(attr=="income" && v[i].income==value){
			info in;
			in.age=v[i].age;in.credit=v[i].credit;in.income=v[i].income;in.student=v[i].student;in.isBuy=v[i].isBuy;
			result.push_back(in);
		}
		
		
		if(attr=="credit" && v[i].credit==value){
			info in;
			in.age=v[i].age;in.credit=v[i].credit;in.income=v[i].income;in.student=v[i].student;in.isBuy=v[i].isBuy;
			result.push_back(in);
		}
		
		
		if(attr=="student" && v[i].student==value){
			info in;
			in.age=v[i].age;in.credit=v[i].credit;in.income=v[i].income;in.student=v[i].student;in.isBuy=v[i].isBuy;
			result.push_back(in);
		}
	}
	return result;
}
//Find the class which is having more occurences
string getMajor(vector<info> &v){
	int yes=0,no=0;
	for(int i=0;i<v.size();i++){
		if(v[i].isBuy=="yes") yes++;
		else no++;
	}
	if(yes>no) return "yes";
	else return "no";
}
//Return the required attribute list
vector<string> getAttrList(string attr,vector<string> &list){
	vector<string> result;
	for(int i=0;i<list.size();i++){
		if(list[i]!=attr){
			result.push_back(list[i]);
		}
	}
	return result;
}
//Print Tree
void print(PTR T){
	PTR tmp=new node;
	tmp->final="null";
	queue<PTR> q;
	q.push(T);
	q.push(tmp);
	while(!q.empty()){
		PTR t=q.front();
		q.pop();
		if(t->final=="null"){
			cout<<endl;
			if(q.empty()){
				break;
			}
			else{
				q.push(t);
			}
		}
		else{
			cout<<"Age"<<setw(16)<<"Income"<<setw(16)<<"Student"<<setw(16)<<"Credit"<<setw(16)<<"Class"<<endl;
			cout<<"---"<<setw(16)<<"------"<<setw(16)<<"-------"<<setw(16)<<"------"<<setw(16)<<"-----"<<endl;
			for(int i=0;i<t->v.size();i++){
				cout<<t->v[i].age<<setw(15)<<t->v[i].income<<setw(15)<<t->v[i].student<<setw(15)<<t->v[i].credit<<setw(15)<<t->v[i].isBuy<<endl;
			}
			cout<<endl;
		}
		for(int i=0;i<t->child.size();i++){
			q.push(t->child[i]);
		}
	}
}
bool f=true;
//Create the Tree
void createTree(PTR &T){
	if(isSameClass(T->v)){
		T->final=T->v[0].isBuy;
		return;
	}
	else if(T->attrList.size()==1){
		T->final=getMajor(T->v);
		return;
	}
	else{
		string attr=AttributeSelection(T->v,T->attrList);
		T->value=getUnique(attr,T->v);
		T->splitClass=attr;
		for(int i=0;i<T->value.size();i++){
			PTR tmp=new node;
			tmp->final="-1";
			tmp->v=getVector(attr,T->value[i],T->v);
			tmp->attrList=getAttrList(attr,T->attrList);
			T->child.push_back(tmp);
		}
		for(int i=0;i<T->value.size();i++){
			createTree(T->child[i]);
		}
	}
}
int main(){
	fstream fin;
	fin.open("Decision.txt");
	PTR T=new node;
	getDataSet(fin,T);
	T->v=information;
	T->final="-1";
	createTree(T);
	print(T);
}
