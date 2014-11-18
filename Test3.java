
public class MainProgram {
    
    public static void main( String[] args ) 
    {
        int i = -1;
        int bbb = 100;
        /*
        while( i < 33 ) {
            System.out.println( i + 1 + toBinary(i) );
            System.out.println( i );

        }
        */
        System.out.println( i + 1 + toBinary( i ) );
        System.out.println( i );
        BaseString cc;
        cc.testA( false );
        String gg;
        gg.testB( 178 );
    }

    public int toBinary( int a ) 
    {
        return a + 1;
    } 

}

class BaseString {
    int a;
    int[] bb;

    public boolean testA( boolean b) {
        a = 10;
        bb[0] = 2;
        return true;
        /*
        if( a && b ) {
            return true;
        } else {
            return false;
        }
        */
    }
}

class String {
    boolean tabs;

    public int testB( int q ) {
        return a + q;
    }


}