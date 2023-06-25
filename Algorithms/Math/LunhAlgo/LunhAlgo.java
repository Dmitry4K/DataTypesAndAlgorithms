public class LunhAlgo {
    public static void main(String[] args) {
        assertSolution("4893470318851588", true);
        assertSolution("48934703188a1588", false);
    }

    private static void assertSolution(String insert, boolean expected) {
        assert new LunhAlgo().isLunhNumber(insert) == expected;
    }

    public boolean isLunhNumber(String cardNumber) {
        if (!cardNumber.matches("[0-9]+")) {
            return false;
        }
        int sum = 0;
        for (int i = 0; i<cardNumber.length(); i++) {
            int number = cardNumber.charAt(i) - '0';
            int term = (((i + 1) % 2) + 1) * number;
            sum += term / 10 + term % 10;
        }
        return sum % 10 == 0;
    }
}
