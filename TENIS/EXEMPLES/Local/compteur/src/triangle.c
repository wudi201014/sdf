int triangle_al_kashi (unit a, uint b, uint c)
{
alpha=((b*b+c*c-a*a)/(2*b*c)) * 180.0 /PI;
beta=((a*a+c*c-b*b)/(2*a*c))* 180.0 /PI;
gamma=((b*b+a*a-c*c)/(2*b*a)) * 180.0 /PI;

if ((alpha + beta + gamma ) != 180.0)
{ return -1;}
else
	if ( a == b) || (b == c)
	{
		return 2;
	}	else
		if ( a == b) && (b == c)  
	{
		return 3;
	}
	 else
		 return 1;
		
	
}

int triangle_petit_cote (unit a, uint b, uint c)
{
if (((a + b) > c) && ((c + b)>a) && ((a+c )> b))
{ 
	if ( a == b) || (b == c)
	{
		return 2;
	}	else
		if ( a == b) && (b == c)  
	{
		return 3;
	}
	 else
		 return 1;
		
	
}else
	return -1;
}



