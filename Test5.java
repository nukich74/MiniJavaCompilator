class Class1 {
	public static void main( String[] args )
	{
			System.out.println(1);
	}
}

class a extends b {
	int a;
	int b;
}

class b extends a {
	int a;
	a b;
}

class c {
	a a;
	b b;
}