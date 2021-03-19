public class RLE {
    static String encode(String text){
        String r = new String();
        if(text.length() > 0) {
            int len = 1;
            char prev = text.charAt(0);
            for(int i = 1;i<text.length();++i){
                char current = text.charAt(i);
                if(current != prev){
                    r = insertToString(r, len, prev);
                    len = 1;
                } else {
                    ++len;
                }
                prev = current;
            }
            r = insertToString(r, len, prev);
        }
        return r;
    }
    static String decode(String text){
        String res = new String();
        if(text.length() > 0) {
            int i = 0;
            while (i < text.length()){
                int num = readNumber(text, i);
                int nextCharIndex = getIndexOfNextChar(text,i);
                for(int j = 0;j<num;++j) {
                    res += String.valueOf(text.charAt(nextCharIndex));
                }
                i = nextCharIndex + 1;
            }
        }
        return res;
    }
    private static int getIndexOfNextChar(String text, int current){
        int i = current;
        while(i < text.length() && isNumber(text.charAt(i))){
            ++i;
        }
        return i;
    }
    private static int readNumber(String text, int pos){
        int i = pos;
        int res = 0;
        if(!isNumber(text.charAt(i))){
            return 1;
        }
        while(i<text.length() && isNumber(text.charAt(i))){
            res *= 10;
            res += text.charAt(i) - '0';
            ++i;
        }
        return res;
    }
    private static boolean isNumber(char a){
        return a <= '9' && a >= '0';
    }
    private static String insertToString(String s, int len, char symbol){
        if(len > 1){
            s += String.valueOf(len);
        }
        s += symbol;
        return s;
    }

    public static void main(String[] args) {
        String string = new String("AAABCCCDE");
        System.out.println(encode(string)); //3AB3CDE
        System.out.print(decode(encode(string)));//AAABCCCDE
    }
}
