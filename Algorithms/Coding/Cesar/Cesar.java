public class Cesar {
    public String code(String text, int shift) {
        if (shift == 0) {
            return new String(text);
        }
        shift = shift % text.length();
        StringBuilder result = new StringBuilder(text.length());
        int startPosition = Math.max(shift, 0);
        int endPosition = Math.min(shift + text.length(), text.length());
        for (int i = 0; i < startPosition; i++) {
            result.append(text.charAt(text.length() - shift + i));
        }
        for (int i = startPosition; i < endPosition; i++) {
            result.append(text.charAt(i - shift));
        }
        for (int i = endPosition; i < text.length(); i++) {
            result.append(text.charAt(i - endPosition));
        }
        return result.toString();
    }

    public String decode(String text, int codingShift) {
        return code(text, -codingShift);
    }

    public static void assertCesarCoding(String insert, int shift, String expected) {
        assert new Cesar().code(insert, shift).equals(expected);
        System.out.println("TEST DONE!");
    }

    public static void assertCesarDecoding(String text, int shift) {
        Cesar cesar = new Cesar();
        assert cesar.decode(cesar.code(text, shift), shift).equals(text);
        System.out.println("TEST DONE!");
    }

    public static void main(String[] args) {
        assertCesarCoding("123", 0, "123"); // 1
        assertCesarCoding("", 0, ""); // 2
        assertCesarCoding("123", -1, "231"); // 3
        assertCesarCoding("123", 1, "312"); // 4
        assertCesarCoding("123", 2, "231"); // 5
        assertCesarCoding("123", 4, "312"); // 6
        assertCesarCoding("123", 2, "231"); // 7
        assertCesarCoding("123", 4, "312"); // 8
        assertCesarCoding("12356789", 3, "78912356"); // 9
        assertCesarCoding("12356789", 4, "67891235"); // 10
        assertCesarCoding("123", -4, "231"); // 11
        assertCesarCoding("123", -5, "312"); // 12
        assertCesarCoding("12356789", -4, "67891235"); // 13
        assertCesarDecoding("123", 2);
        assertCesarDecoding("123", -2);
        assertCesarDecoding("123", 0);
        assertCesarDecoding("123", 4);
        assertCesarDecoding("123", -4);
        assertCesarDecoding("123456778", -4);
        assertCesarDecoding("123456778", 4);
    }
}