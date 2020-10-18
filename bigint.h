#include <bits/stdc++.h>
using namespace std;
string tensc(string b);
string zero(int x);
string add(string a, string b);
string sub(string a, string b);
string mul(string a, string b);
string hcf(string a, string b);
string fast_pow(string base,string exp);
bool isZero(string a);
pair<string,string> div(string a, string b);
string fact(string a);
// int main()
// {
// 	ios_base::sync_with_stdio();
// 	cin.tie(0);
// 	cout.tie(0);
// 	string a,b;
// 	int T,k;
// 	cin>>T;
// 	pair<string,string> p ;
// 	while(T--)
// 	{
// 		cin>>k;
// 		if(k==1)
// 		{
// 			cin>>a>>b;
// 			cout<<fast_pow(a,b)<<endl;
// 		}
// 		else if(k==2)
// 		{
// 			cin>>a>>b;
// 			cout<<hcf(a,b)<<endl;
// 		}
// 		else if(k==3)
// 		{
// 			cin>>a;
// 			cout<<fact(a)<<endl;
// 		}
// 		else 
// 		{
// 			cout << "Wrong Choice : \n Choose 1 for pow function.\n Choose 2 for gcd of two numbers. \n Choose 3 for finding factorial of a number.\n";
// 		}
// 	}
// }

string add(string a, string b)
{
	string c = "";
	bool flag = false;
	if ((a[0] == '-') && (b[0] != '-')) 
	{                                                           
		a = a.erase(0,1);
		 c = sub(b,a);
		 return c;
	}
	else if ((a[0] != '-') && (b[0] == '-'))
	{
		b =  b.erase(0,1);
		c= sub(a,b);
		return c;
	}
	else
	{
		if((a[0] == '-') && (b[0] == '-'))
		{
			flag = true;
			a.erase(0,1);
			b.erase(0,1);
		}

	
	int temp = 0,carry = 0,i = 0;
	
	if( a.size() < b.size())
	{
		string  t = a;
				a = b;
				b = t;
	}
	a = "0" + a;
	int alen = a.size();
	int blen = b.size();
	while(i < alen )
	{
		if(i < blen)
			temp = carry + (a[alen-1-i]-'0') + (b[blen-1-i]-'0');
		else
			temp = carry + (a[alen-1-i]-'0');
		carry = temp/10;

		c  = to_string(temp%10) + c;
		i++;
	}
	//***************************** code to remove leading zeros****************************
	string result = "";
	for ( i=0;i<c.size();i++)
		{
			if( c[i]!= '0')
				break;
		}
		for (;i<c.size();i++)
			result += c[i];
	//******************************************************************************************
	if (flag)
		result = '-'+result;
	return result;
	}
}
string sub(string a, string b)
{
	string c="";
	int i=0;
	int flag = 0;		//this is set when |b| > |a|

if ((a[0] == '-') && (b[0] != '-'))
{
	b = '-'+ b;
	c = add(a,b);
	return c;
}
else if ((a[0] != '-') && (b[0] == '-'))
{	
	b = b.erase(0,1);
	c = add(a,b);
	return c;
}
else if ((a[0] == '-') && (b[0] == '-'))
{
	b = b.erase(0,1);
	a = a.erase(0,1);

	c = sub(b,a);
	return c;
}
//***************** the real deal**********************************
 else if ((a[0] != '-') && (b[0] != '-'))
 {
 	//cout<<"no -"<<endl;
 	if (a.size() > b.size())
 	{
 		b = zero(a.size()-b.size()) + b;
 	}
 	else	//number of digits in b is greater or equal to a
 	{
 		if(a.size() == b.size())
 		{
 			if (b > a)
 			{
 				c = sub(b,a);
 				c= '-' + c;
 				return c;
 			}

 		}
 		if (a.size() < b.size())
 		{
 			a = zero(b.size()-a.size()) + a ;
 			c=sub(a,b);
 			return c;
 		}
 	}
 	//*************calling 10's complement function*************
 	b = tensc(b);

c = add(a,b);
if(flag)
	c=tensc(c);
c=c.erase(0,1);
//***************************** code to remove leading zeros****************************
	string result = "";
	for ( i=0;i<c.size();i++)
		{
			if( c[i]!= '0')
				break;
		}
		for (;i<c.size();i++)
			result += c[i];
	//******************************************************************************************
		if (flag)
			result = '-' + result;
		if(result == "")
			result="0";
return result;
}
return "error";
}


string zero(int x)
{
	string z="";
	for (int i=0;i<x;i++)
		z+="0";
	return z;
}
string tensc(string b)
{
	for(int i=b.size()-1;i>=0;i--)
{
	b[i] = '9'+'0' - b[i];
}
if (b[b.size()-1] != '9')
	b[b.size()-1] = b[b.size()-1] +'1'-'0';
else
{
	b[b.size()-1] ='0';
	if (b.size()>1)
		b[b.size()-2] = b[b.size()-2] +'1'-'0';
}
return b;
}
string mul(string a, string b)
{
	int flag = 0;
	if( a[0] != '-' && b[0] == '-') 
	{
		flag = 1;
		b = b.erase(0,1);
	}
	else if (( a[0] == '-' && b[0] != '-'))
	{
		flag = 1;
		a = a.erase(0,1);
	}
	else if ( a[0] == '-' && b[0] == '-')
	{
		a = a.erase(0,1);
		b = b.erase(0,1);
	}
	string prod = "0";
	string c="",temp_swap="";
	int temp=0,zero_count_of_a=0,carry=0,result=0,zero_count_of_b=0;
	//*****************************code to remove trailing zeros and keep the count*****
	// for(int i=a.size()-1;a[i]!='0';i--)
	// 	zero_count_of_a++;
	// 	a = a.substr(0,(a.size()-zero_count_of_a));
	// for(int i=b.size()-1;b[i]!='0';i--)
	// 	zero_count_of_b++;
	// 	b = b.substr(0,(b.size()-zero_count_of_b));
	//**********************************************************************************
		// int zero_count = zero_count_of_a + zero_count_of_b;
		// cout<<zero_count<<endl;
	//***************************** code to remove leading zeros****************************
	string zerofree = "";
	int i=0;
	for ( i=0;i<a.size();i++)
		{
			if( a[i]!= '0')
				break;
		}
		for (;i<a.size();i++)
			zerofree += a[i];
	//******************************************************************************************
		a = zerofree;
		//***************************** code to remove leading zeros****************************
	zerofree = "";
	for ( i=0;i<b.size();i++)
		{
			if( b[i]!= '0')
				break;
		}
		for (;i<b.size();i++)
			zerofree += b[i];
	//******************************************************************************************
		b = zerofree;
	for(int i= b.size()-1;i>=0;i--)
	{
		c = "";
		carry=0;
		for(int j= a.size()-1;j>=0;j--)
		{
			result = (a[j] - '0') * (b[i] - '0');
			temp = carry + result;
			carry = temp/10;
			c =  to_string(temp%10) + c ;
			
			if(j == 0 && carry > 0)
				c = to_string(carry) +c;
		}
		c = c + zero(b.size()-i-1);
		prod = add(prod,c);
	}
	if (flag)
		prod= '-' + prod;
	return prod;
}

pair<string,string> div(string number,string divisor)
{



//***************************** code to remove leading zeros****************************
	string result = "";int i = 0;
	for ( i=0;i<number.size();i++)
		{
			if( number[i]!= '0')
				break;
		}
		for (;i<number.size();i++)
			result += number[i];
		number=result;
	//******************************************************************************************
		//***************************** code to remove leading zeros****************************
	result = "";
	for ( i=0;i<divisor.size();i++)
		{
			if( divisor[i]!= '0')
				break;
		}
		for (;i<divisor.size();i++)
			result += divisor[i];
		divisor = result;
	//******************************************************************************************

	// As result can be very large store it in string 
    string quotient,remainder; 
    int flag=0;				//even flag i.e flag =0,2 means positive quotient
    pair <string,string> ans;
    
    if (number[0] == '-')
    {
    	number = number.erase(0,1);
    	flag++;
    }
    if (divisor[0] == '-')
    {
    	divisor = divisor.erase(0,1);
    	flag++;
    }
    if(number.size() <= divisor.size())
    	{
    		if(number < divisor)
    		{
    			ans.first = (quotient = "0");
    			ans.second = (remainder = number);
    			return ans;
    		}
    	}
    // Find prefix of number that is larger 
    // than divisor. 
    int idx = divisor.size(); int q=0;
    string temp = number.substr(0,idx);
    if (temp < divisor) 
    {
    	//cout<<"hi"<<endl;
       temp = temp + number[idx++]; 
    }
    string residue = temp;	// stores the value after each substraction.
      // string residue;
    // Repeatedly divide divisor with temp. After  
    // every division, update temp to include one  
    // more digit. 
    
int z=0;
    while (number.size() >= idx) 
    { 
        q=0;
          while(residue[0] != '-')	//while the substraction fetches +ve result 	
          		{	
          			if(isZero(residue))
          			{
          				z=1;
          				break;
          			}
          		residue = sub(residue,divisor);
          		if(residue[0] != '-')
          			q++;
          		}		
          		quotient = quotient + to_string(q); 		// storing the quotient obtained in each step
          		if (z !=1)
          			temp = add(residue,divisor);
          		else 
          			temp="";
          		z=0;
          		if (idx == number.size())
          			break;				
          		temp = temp + number[idx++]; 				//updates the dividend for division again.
          		residue = temp;
    } 
    if (flag%2 != 0)
    	quotient = '-' + quotient; 
    if (temp=="")
    	remainder="0";
    else
    	remainder = temp;
    ans.first = quotient ;
    ans.second = remainder ;
      
    return ans; 
}

string fact(string a)
{
	string s = "1";
	if(a[0] == '-')
		return "Invalid input";
	while(a > "0")
		{
			s = mul(s,a);
			a = sub(a,"1");
		}
	return s;
}

bool isZero(string a)
{
	int flag=0;
	for(int i=0;i<a.size();i++)
	{
		if(a[i] != '0')
		{
			flag=1;
			break;
		}
	}
	if(flag)
		return false;
	else 
		return true;
}
string hcf(string a, string b)
{
	string q, r;
	pair<string,string> result;
	// loop till remainder is 0
		while(!isZero(b))
	{
		result = div(a,b);		// quotient 
		q = result.first;
		r = result.second;

		// or we can simply use (a % b) to calculate r

		// a becomes b and b becomes r (a % b)
		a = b;
		b = r;
	}

	return a;
}

string fast_pow(string base,string exp)
{
    string temp,q,r; 
    if( isZero(exp)) 
        return "1"; 
    temp = fast_pow(base, (q = (div(exp,"2")).first)); 
    if (isZero(r =(div(exp,"2")).second)) 
        return mul(temp,temp); 
    else
        return mul(base,mul(temp,temp));  
}