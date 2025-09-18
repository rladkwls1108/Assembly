public class wb8 {
    public static void main(String[] args){
        int Y;
        int X = ((Y = 0) + 4) * 3;
        System.out.println(X);
    }
}
// javac wb8.java
// javap -c wb8   ← 바이트코드 확인
