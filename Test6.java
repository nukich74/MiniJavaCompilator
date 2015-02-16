class MainProgram {
	public static void main( String[] args )
	{
		System.out.println( 1 );
	}
}

class MainProgram22 {
	public int aaaaaa()
	{
		//a = 1 + i;
		int i;
		i = 0;
		while( i < 33 ) {
			System.out.println( i + 1 );
			System.out.println( i + 5 );
		}
		System.out.println( 1 + i );
		System.out.println( 1 );
		return 5;
	}
}

class BaseString {
	int a;
	int[] bb;
}

class NotString extends BaseString {
	boolean tabs;
	public int testB( int q )
	{
		if( a < 5 && q < 0 ) {
			q = 3;
		} else {
			q = 10;
		}
		return a + q;
	}

	public boolean testC( boolean flag, int[] array )
	{
		int variable;
		//int[] array;
		int variable2;
		boolean flag2;
		BaseString parent;

		return true;
	}
}

class BaseString2 {
	int a;
	int b;
	//boolean a;

	public boolean testBase()
	{
		int a;
		return true;
	}
	public int testBase2( int flag )
	{
		int b;
		return b;
	}
}