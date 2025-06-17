#include<stdio.h>//素数之积一定为合数
#include<math.h>
void factorize(int a,int array[100][2]);
int prime(int a);
double decode(int a, int b, int c);
int gcd(int a, int b);
/*void RelativelyPrime(int a, int array[100]);//这里特别注意一下数组作为函数参数的时候形参实参应该怎么写*/
int main()
{
	int o;
	scanf("%i", &o);
	if (o == 1)
	{
		int p;
		int q;
		int m;
		int a;//这个用来选取
		int b = 0;
		int t;//茶壶
		int phi;
		scanf("%i", &p);
		scanf("%i", &q);
		scanf("%i", &m);//先输入pq再输入明文m
		phi = (p - 1) * (q - 1);
		int e[100] = { 0 };//存放e
		for (int g = 1; g <= 50; g++)//进行100次选取e,现在g代表的是e
		{
			if (gcd(phi, g) == 1)
			{
				e[b] = g;
				b = b + 1;
			}
		}
		for (int g = 0; g < 100; g++)
		{
			if (e[g] != 0)
			{
				printf("%i ", e[g]);
			}
		}//将会展示有哪些e可以被选择
		scanf("%i", &a);
		double d;
		int h[10000] = { 0 };
		b = 0;
		for (int k = 1; k <= 100; k++)
		{
			d = ((k * phi) + 1) / e[a];
			if (double(int(d)) == d || int(d) != 0)
			{
				h[b] = int(d);
				b = b + 1;
				if (b == 10)
				{
					break;
				}
			}
		}
		int j;
		j = decode(m, e[a], p * q);
		printf("%i\n", j);
		printf("%i", h[5]);//展示密文和密钥之一
	}
	if (o == 0)
	{
		int n;//用于存放密钥n
		scanf("%i", &n);
		int z[100][2] = { 0 };//用于存放可能的密钥n的一个因数,正是这个因数的多样,导致了φ的多样,导致了解密钥的多样,导致了结果的多样
		factorize(n, z);//这里的意思是分解n,并将可能的质因数放到z中
		int y[100] = { 0 };//用于存放φ的可能值
		int x;//用于循环控制	
		for (x = 0; x < 100; x++)
		{
			y[x] = (z[x][0] - 1) * (z[x][1] - 1);
		}//现在y被填满了φ的可能值
		int c[100] = { 0 };//用于存放可能的与φ互质的数
		/*RelativelyPrime(φ, c);//此时数组c里面存留有e*/
		double d;//将被破解的解密钥d,d的不同来源于φ的不同
		int e;//用于存放给出的e
		int f;//用于循环控制
		int g[10000] = { 0 };
		int h = 0;//用于循环控制
		scanf("%i", &e);
		for (x = 0; x < 100; x++)
		{
			for (f = 1; f < 100; f++)
			{
				d = ((f * y[x]) + 1) / e;//遍历φ,则容易遍历d,d可能会出现多种情况,所以我想将其保存在数组中
				if (double(int(d)) == d)//先化为int去尾再化为double方便比较,这里判断是不是整数,也就是如果d是整数则将d存放在g[h]中
				{
					g[h] = d;
					h = h + 1;
					if (h == 100)
					{
						break;
					}
				}
			}
			break;
		}//现在g数组中被充满了可能的d,这里会出错?!只是double精度问题,把一些不与原数相等的也放到里面去了,原数相等的情况还是会包括在里面,问题不大,多算几遍而已
		/*for (x = 0; x < 100; x++)
		{
			for (f = 1; f < 100; f++)
			{
				d = ((f * y[x]) + 1) / e;//遍历φ,则容易遍历d,d可能会出现多种情况,所以我想将其保存在数组中
				if (double(int(d)) == d)//先化为int去尾再化为double方便比较,这里判断是不是整数,也就是如果d是整数则将d存放在g[h]中
				{
					g[h] = d;
					h = h + 1;//唐突这样会导致数组溢出
				}
			}
		}//现在g数组中被充满了可能的d*/
		/*for (f = 1; f < 100; f++)
		{
			for (x = 0; x < 100; x++)
			{
				d = ((f * y[x]) + 1) / e;//遍历φ,则容易遍历d,d可能会出现多种情况,所以我想将其保存在数组中
				if (double(int(d)) == d)//先化为int去尾再化为double方便比较
				{
					for (h = 0; h < 100; h++)
					{
						g[h] = d;
					}
				}
			}
		}//现在g数组中被充满了可能的d,这个循环这样设计是有问题的,f要等到内循环全执行完一次之后才动,所以这里要改变f的位置,参上*/
		int i;//用于存放密文
		int j;//用于存放明文
		scanf("%i", &i);
		for (h = 0; h < 100; h++)
		{
			double k;
			k = decode(i, g[h], n);
			j = (int(decode(i, g[h], n))) % n;
			printf("%i\n", j);
		}
	}
	return 0;
}
void factorize(int a,int array[100][2])//这个函数会将n分解为两个素数,这个函数编写完成
{
	int b;//用于循环控制,并且表示分解a的一个因数,我将其限制在100以内,否则解密情况过大
	int c;//用于循环控制,并且表示分解a的一个因数,我将其限制在100以内,否则解密情况过大
	int d = 0;//用于循环控制
	for (b = 2; b < 100; b++)
	{
		if (prime(b))//如果b是素数的话
		{
			for (c = 2; c < 100; c++)
			{
				if (prime(c))//如果c是素数的话
				{
					/*for (d = 0; d < 100; d++)
					{
						if (a == b * c)//如果a等于b+c成立的话,输出b和c,这个函数目的是分解由两个素数相乘所得的密钥n
						{
							array[d][0] = b;
							array[d][1] = c;
						}
					}//我想真的存在a的时候才给数组赋值*/
					/*if (a == b * c)//如果a等于b+c成立的话,输出b和c,这个函数目的是分解由两个素数相乘所得的密钥n
					{
						for (d = 0; d < 100; d++)
						{
							array[d][0] = b;
							array[d][1] = c;
						}
					}*/
					if (a == b * c)
					{
						array[d][0] = b;
						array[d][1] = c;
						d = d + 1;
					}//上面两种结构都是不行的,只有这种结构才可以
				}
			}
		}
		//break;
	}//如果想设置得到第一组后两个循环同时break但出现错误,所以保留原函数情况
}//特别注意,这个函数没有考虑n可能被分解成两种b*c的情况,所以是取最后一种的
int prime(int a)//这个函数用于素数判断,如果不是素数则返回0,是素数则返回1,这个函数编写完成
{
	int b;//用于循环控制
	if (a == 0 || a == 1)
	{
		return 0;//0和1不是素数,特判一下
	}
	else if (a == 2)
	{
		return 1;//2是素数,特判一下
	}
	else//判断
	{
		for (b = 2; b <= sqrt(a); b++)
		{
			if (a % b == 0)
			{
				break;
			}
		}
		if (a % b == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}
/*void RelativelyPrime(int a, int array[100])//这个函数用于寻找φ的互质的数,返回一个互质的数,想检测所有可能并把所有可能放在数组中,这个在主函数实现,这里主要实现互质判断
{
	int b;//用于判断b是不是与φ互质
	int c;//用于循环判断
	for (b = 0; b < 100; b++)
	{
		if (a % b != 0)//则互质
		{
			for (c = 0; c < 100; c++)//放入数组中
			{
				b = array[c];
			}
		}
	}
}//之前我想用一个非常抽风的方法,就是分解φ,然后分解2到100的所有数,把前者的因数和后者的因数比较实现互质判断,但这是基本不可能的*/
//这段我本来想遍历寻找与φ互质的数e,但是e是给出来的,所以没必要找
double decode(int a,int b,int c)//这个函数用于对c的d次方进行取n的模的解密,用到循环方法,其中a输入的是密文,b输入的是幂,c输入的是模
{
	int d;//用于循环控制
	int f = 1;//用于返回最终值
	for (d = 1; d <= b; d++)
	{
		f = f * a % c;//第一次f得到cmodn,也就是amodc,第二次f得到cmodn*cmodn,得到了模
	}
	return f;//返回f
}//这个函数编写完成
int gcd(int a, int b)
{
	while (b != 0)
	{
		int t = a % b;
		a = b;
		b = t;
	}
	return a;
}//之前提到这里能不能用高精度计算?个人认为高精度计算只能用在输出,因为oj系统不会判断你输出的是数据是什么类型,我想输出114514
//那我可以使用int a=114514;printf("%i",a);我也可以使用for循环输出数组int a[6]={1,1,4,5,1,4};
//也就是说,高精度计算只能用于输出,不能用高精度计算的结果来进行其他运算
//在rsa的取模加密解密中,即使我采用高精度进行幂运算,下一步这个运算结果还是得被取模,这是使用高精度进行幂运算输出的结果做不到的(无法对高精度计算的结果进行取模)
//所以这里一定只能使用快速幂取模算法
//2024.11.27 11:20