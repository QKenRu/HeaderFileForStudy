#ifndef STRING_H
#define STRING_H
#include<iostream>
using namespace std;
class String
{
private:
	char *str;
	int size;
public:
	//构造和析构
	String(const char *c = ""):size(0),str(0) { *this = c; } //转换和默认构造
	String(const String &s):size(0),str(0) { *this = s; } //复制构造
	~String() { delete[]str; } //析构
	//赋值
	String &operator=(const char *c); //转换赋值：类串=C串
	String &operator=(const String &s) { return *this = s.str; } //复制赋值：类串=类串
	//输入输出
	friend istream &operator>>(istream &istr,String &s); //提取符
	friend ostream &operator<<(ostream &ostr,const String &s); //插入符
	//连接
	String operator+(const String &s) const; //类串+类串
	String operator+(const char *c) const; //类串+C串
	friend String operator+(const char *c,const String &s); //C串+类串
	//插入和删除
	String &Insert(int id,const String &s); //插入类串
	String &Insert(int id,const char *c); //插入C串
	String &Erase(int id,int num); //删除子串
	//取子串
	String SubStr(int id,int num) const; //取子串
	//查找
	int FindFirstOf(char ch,int id) const; //从id开始查找ch首次出现的位置
	int FindFirstOf(const String &s,int id) const;
	int FindFirstOf(const char *c,int id) const{ return FindFirstOf(String(c),id); }
	int Size() { return size; }
	//索引
	char &operator[](int id) { return str[id]; }
	const char &operator[](int id) const{ return str[id]; }
	//字符串求长
	int Strlen(const char *s)const;
	//字符串复制
	char *Strcpy(char *s1,const char *s2)const;
	char *Strncpy(char *s1, char *s2, int n)const;
	//字符串连接
	char *Strcat(char *s1,char *s2)const;
	char *Strncat(char *s1,char *s2,int n)const;
	//字符串大小写替换
	String &Strupr(String &s);
	String &Strlwr(String &s);
	//字符串比较
	static int Strcmp(const char *s1,const char *s2); //完整字符串比较
	static int Strncmp(const char *s1,const char *s2,int n); //指定前n个字符的字符串比较

	//关系运算
	bool operator==(const String &s) const
	{
		return Strcmp(str, s.str) == 0; //类串==类串
	}
	bool operator==(const char *c) const
	{
		return Strcmp(str, c) == 0; //类串==C串
	}
	friend bool operator==(const char *c, const String &s)
	{
		return Strcmp(c, s.str) == 0; //C串==类串
	}
	bool operator>(const String &s) const
	{
		return Strcmp(str, s.str) > 0; //类串>类串
	}
	bool operator>(const char *c) const
	{
		return Strcmp(str, c) > 0; //类串>C串
	}
	friend bool operator>(const char *c, const String &s)
	{
		return Strcmp(c, s.str) > 0; //C串>类串
	}
};

int String::Strlen(const char *s)const
{
	int i=0;
	while(s[i]!='\0')
	{
		++i;
	}
	return i;
}

int String::Strcmp(const char *s1,const char *s2)
{ //将字符串s1和s2的字符从前往后逐个比较，都相等时返回0，不等时比较停止，前者大时返回1，后者大时返回-1
	int i=0; //数据元素索引
	int token=0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			break;
		}
		++i;
	}
	if(s1[i]>s2[i]) //'\0'的ASCII码为0，比任何字符都要小，
	{
		token=1;
	}
	else if(s1[i]<s2[i])
	{
		token=-1;
	}
	return token;
}
int String::Strncmp(const char *s1,const char *s2,int n)
{ //将字符串s1和s2的前n个字符从前往后比较
	int i=0,token=0;
	while(i<n && s1[i]!='\0' && s2[i]!='\0')
	{
		if(s1[i]!=s2[i])
		{
			break;
		}
		++i;
	}
	if(s1[i]>s2[i])
	{
		token=1;
	}
	else if(s1[i]<s2[i])
	{
		token=-1;
	}
	return token;
}

char *String::Strcpy(char *s1,const char *s2)const
{ //将源字符串s2复制到目标字符串或目标字符数组s1，返回指针s1
	int i=0;
	while(s2[i]!='\0')
	{
		s1[i]=s2[i++];
	}
	s1[i]='\0';
	return s1;
}
char *String::Strncpy(char *s1,char *s2,int n)const
{ //将源字符串s2的前n个字符替换目标字符串s1的前n个字符，返回指针s1
	int i;
	int token=1;
	if(Strlen(s1)<n)
	{
		token=0;
	}
	for(i=0;i<n;++i)
	{
		s1[i]=s2[i];
	}
	if(token==0)
	{
		s1[i]='\0';
	}
	return s1;
}

char *String::Strcat(char *s1,char *s2)const
{
	int i=Strlen(s1); //字符串s1的结束符索引
	int j=0; //字符串s2的索引
	while(s2[j]!='\0')
	{
		s1[i++]=s2[j++];
	}
	s1[i]='\0';
	return s1;
}
char *String::Strncat(char *s1,char *s2,int n)const
{
	int i=Strlen(s1);
	int j=0;
	while(j<n && s2[j]!='\0')
	{
		s1[i++]=s2[j++];
	}
	s1[i]='\0';
	return s1;
}

String &String::Strupr(String &s)
{
	for(int i=0;i<s.Size();++i)
	{
		if(s.str[i]>96 && s.str[i]<123) //小写字母的ASCII码
		{
			s.str[i]-=32; //加32就是大写字母的ASCII码
		}
	}
	return s;
}

String &String::Strlwr(String& s)
{
	for(int i=0;i<s.Size();++i)
	{
		if(s.str[i]>64 && s.str[i]<91)
		{
			s.str[i]+=32;
		}
	}
	return s;
}

String &String::operator=(const char *c) //转换赋值：类串=C串
{
	delete []str;
	int len = Strlen(c);
	str = new char[len + 1];
	if (str==0)
	{
		cout << "operator=:overflow!";
		exit(1);
	}
	Strcpy(str,c);
	size = len;
	return *this;
}
ostream &operator<<(ostream &ostr,const String &s)
{
	ostr << s.str;
	return ostr;
}
istream &operator>>(istream &istr,String &s)
{
	char buf[80]; //缓冲器。一行输入最多80个字符
	cin.get(buf,80); //从键盘输入1个字符串进入缓冲器
	cin.get(); //清空输入缓冲器
	s = buf;
	return istr;
}
String String::operator+(const String &s) const //类串+类串
{
	String w; //新串
	delete[]w.str;
	w.size = size + s.size;
	w.str = new char[w.size + 1];
	Strcpy(w.str,str); //将左元中的C串复制到新串
	Strcat(w.str,s.str); //将右元中的C串连接到新串中的C串
	return w;
}
String String::operator+(const char *c) const //类串+C串
{
	String w(c); //转换构造，生成类串w
	w = *this + w; //类串+类串和复制赋值
	return w;  //返回赋值后的类串
}
String operator+(const char *c,const String &s) //在索引id处插入一个类串
{
	String w(c); //调用转换构造，生成类串w
	w = w + s; //调用“类串+类串”和复制赋值
	return w;
}
String &String::Insert(int id,const String &s) //子串插入
{
	String old(*this); //保留调用对象
	str = new char[size + s.size + 1]; //重新分配调用对象的空间
	if (str == 0)
	{
		cout << "overflow!";
		exit(1);
	}
	Strcpy(str,old.str); //取回原调用对象的值
	Strcpy(old.str,str + id); //保留调用对象中要移动的子串
	Strcpy(str + id,s.str); //在插入位置复制要插入的子串
	Strcat(str,old.str); //将保留的移动子串连接到调用对象
	size = size + s.size;
	return *this;
}
String &String::Insert(int id,const char *c) //在索引id处插入C串
{
	String w(c); //转换构造生成类串
	Insert(id,w); //插入类串插入函数
	return *this;
}
String &String::Erase(int id,int num) //删除子串
{
	if (size - id < num)
		num = size - id;
	String old(str + id + num);
	Strcpy(str + id,old.str);
	old = str;
	*this = old;
	return *this;
}
String String::SubStr(int id,int num) const //取子串
{
	if (size - id < num)
		num = size - id;
	String w(str + id);
	w.Erase(num,w.size - num);
	return w;
}
int String::FindFirstOf(char ch,int id)const //从id开始查找ch首次出现的位置
{
	for (int i = id; str[i] != '\0'; ++i)
		if (str[i] == ch)
			return i;
	return -1;
}
int String::FindFirstOf(const String &x,int id) const
{
	char firstch = x.str[0],lastch = x.str[x.size - 1];
	int firstid = FindFirstOf(firstch,id);
	int lastid = firstid + x.size - 1;
	while (firstid != -1 && lastid < size)
	{
		if (str[lastid] == lastch)
		{
			if (SubStr(firstid,x.size) == x)
				return firstid;
		}
		id = firstid + 1;
		firstid = FindFirstOf(firstch,id);
		lastid = firstid + x.size - 1;
	}
	return -1;
}
#endif