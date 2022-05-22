import java.util.HashMap;
import java.util.Map;

class Solution {
    Map<Integer, Boolean> memo = new HashMap<Integer, Boolean>();

    public boolean canIWin(int maxChoosableInteger, int desiredTotal) {
        if ((1 + maxChoosableInteger) * (maxChoosableInteger) / 2 < desiredTotal) {
            return false;
        }
        return dfs(maxChoosableInteger, 0, desiredTotal, 0);
    }

    public boolean dfs(int maxChoosableInteger, int usedNumbers, int desiredTotal, int currentTotal) {
        if (!memo.containsKey(usedNumbers)) {
            boolean res = false;
            for (int i = 0; i < maxChoosableInteger; i++) {
                if (((usedNumbers >> i) & 1) == 0) {
                    if (i + 1 + currentTotal >= desiredTotal) {
                        res = true;
                        break;
                    }
                    if (!dfs(maxChoosableInteger, usedNumbers | (1 << i), desiredTotal, currentTotal + i + 1)) {
                        res = true;
                        break;
                    }
                }
            }
            memo.put(usedNumbers, res);
        }
        return memo.get(usedNumbers);
    }
}

//
//
//class Solution {
//    Set<Integer> space=new HashSet<>();
//    Map<Set<Integer>,Boolean> memo=new HashMap<>();
//    public boolean canIWin(int maxChoosableInteger, int desiredTotal) {
//        if((1+maxChoosableInteger)*maxChoosableInteger/2<desiredTotal)return false;
//        Set<Integer> space=new HashSet();
//        for(int i=0;i<maxChoosableInteger;i++){
//            space.add(i+1);
//        }
//        return dfs(maxChoosableInteger,space,desiredTotal,0);
//    }
//    public boolean dfs(int maxChoosableInteger, Set<Integer> space, int desiredTotal, int current) {
//        if (!memo.containsKey(space)) {
//            boolean sign=false;
//            for (int i = 0; i < maxChoosableInteger; i++) {
//                if (space.contains(i + 1)){
//                    if (current + i + 1 >= desiredTotal) {//自己成功
//                        sign=true;
//                        break;
//                    }
//                    space.remove(i+1);
//                    if(!dfs(maxChoosableInteger,space, desiredTotal, current + i + 1)){//别人失败
//                        sign=true;
//                        space.add(i+1);
//                        break;
//                    }
//                    space.add(i+1);
//                }
//
//            }
//            memo.put(space, sign);
//        }
//        return memo.get(space);
//    }
//}