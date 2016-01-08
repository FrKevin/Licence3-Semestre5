public class Synch extends Thread {
    private int c1, c2, c3;
    final static int ITER = 10000000;

    public void m1() {
        for(int i = 0; i < Synch.ITER; i++) {
            synchronized(this) {
                c1 ++;
            }
            c2 ++;
        }
    }

    public void m2() {
        for(int i = 0; i < Synch.ITER; i++) {
            synchronized(this) {
                c1 ++;
            }
            c3 ++;
        }
    }

    public void run() {
        m1();
    }

    public String toString() {
        return "1: " + this.c1 + "\n2: " + this.c2 + "\n3: " + this.c3;
    }

    public static void main(String argv[]) throws Exception {
        Synch s = new Synch();

        s.start();
        s.m2();
        s.join();

        System.out.println(s);
    }
}
