import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;


public class Solution {

    private Scanner reader = new Scanner(new BufferedReader(new InputStreamReader(System.in)));
    private void process() {
        T = reader.nextInt();
        for (int i = 1; i <= T; i++) {
            dataRead();
            solve(i);
        }
    }

    private int nextInt() {
        return reader.nextInt();
    }
    private long nextLong() {
        return reader.nextLong();
    }
    private float nextFloat() {
        return reader.nextFloat();
    }
    private double nextDouble() {
        return reader.nextDouble();
    }
    private String nextString() {
        return reader.next();
    }

    private int T;
    private int L;
    char[] S = new char[1000001];
    private long N, A, B, C, D;
    private List<String> words;

    class KEY {
        public char st;
        public char ed;
        public List<Integer> cnt;

        public void removeFirst() {
            int v = cnt.get(st - 'a');
            cnt.set(st - 'a', v - 1);
        }

        public void addLast(char e) {
            int v = cnt.get(e - 'a');
            cnt.set(e - 'a', v + 1);
            ed = e;
        }

        private boolean countEqual(List<Integer> x) {
            for (int i = 0; i < 26; i++) {
                if (!x.get(i).equals(cnt.get(i))) {
                    return false;
                }
            }
            return true;
        }

        @Override
        public boolean equals(Object otherObj) {
            if (otherObj == null) {
                return false;
            }
            if (otherObj == this) {
                return true;
            }
            if (!(otherObj instanceof KEY)) {
                return false;
            }
            KEY other = (KEY) otherObj;
            return st == other.st && ed == other.ed && countEqual(other.cnt);
        }

        @Override
        public int hashCode() {
            int h = 1;
            h = h * 31 + st;
            h = h * 31 + ed;
            for (int i = 0; i < cnt.size(); i++) {
                h = h * 31 + cnt.get(i);
            }
            return h;
        }
    };

    KEY build(char st, char ed, int[] cnt) {
        KEY key = new KEY();
        key.st = st;
        key.ed = ed;
        key.cnt = new ArrayList<>();

        for (int i = 0; i < 26; i++) {
            key.cnt.add(cnt[i]);
        }
        return key;
    }

    private void dataRead() {
        L = nextInt();
        words = new ArrayList<>();
        for (int i = 0; i < L; i++) {
            words.add(nextString());
        }

        String s1 = nextString();
        String s2 = nextString();
        N = nextLong();
        A = nextLong();
        B = nextLong();
        C = nextLong();
        D = nextLong();
        long x = S[0] = s1.charAt(0);
        long y = S[1] = s2.charAt(0);
        for (int i = 2; i < N; i++) {
            long z = (A * y % D + B * x % D + C) % D;
            x = y;
            y = z;
            S[i] = (char)(z % 26 + 'a');
        }
    }

    int[] countAlpha(String s) {
        int[] cnt = new int[26];
        for (char c : s.toCharArray()) {
            cnt[c - 'a']++;
        }
        return cnt;
    }

    private void solve(int ca) {
        int ans = 0;
        Map<KEY, Integer> wordCountMap = new HashMap<>();
        Set<Integer> lengths = new HashSet<>();
        for (String word : words) {
            if (word.length() > N) {
                continue;
            }
            lengths.add(word.length());
            int[] cnt = countAlpha(word);
            char st = word.charAt(0);
            char ed = word.charAt(word.length() - 1);
            KEY wordFeature = build(st, ed, cnt);
            //System.out.println(word + " " + wordFeature.hashCode());
            Integer x = wordCountMap.getOrDefault(wordFeature, 0);
            wordCountMap.put(wordFeature, x + 1);
        }


        for (int len : lengths) {
            int[] scnt = new int[26];
            for (int i = 0; i < len - 1; i++) {
                scnt[S[i] - 'a']++;
            }
            KEY feat = build(S[0], S[len - 1], scnt);
            for (int i = 0; i <= N - len; i++) {
                char st = S[i];
                char ed = S[i + len - 1];
                feat.st = st;
                feat.addLast(ed);
                int c = wordCountMap.getOrDefault(feat, 0);
                if (c > 0) {
                    ans += c;
                    wordCountMap.remove(feat);
                }
                feat.removeFirst();
            }
        }
        System.out.println("Case #" + ca + ": " + ans);
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        solution.process();
    }
}

