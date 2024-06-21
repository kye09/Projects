package POS;

import java.util.ArrayList;
import java.util.List;

interface DeliPos {
    void subcustmer(Custmer custmer);

    void deletecustmer(Custmer custmer);

    void notifyCustmer(String msg);
}

interface Custmer {
    void update(String msg);
}

public class DeliveryPos implements DeliPos {
    private List<Custmer> custmers = new ArrayList<>();

    public void arrival() {
        notifyCustmer("택배가 도착했습니다.");
    }

    public void subcustmer(Custmer custmer) {
        custmers.add(custmer);
    }

    public void deletecustmer(Custmer custmer) {
        custmers.remove(custmer);
    }

    public void notifyCustmer(String msg) {
        custmers.forEach(custmer -> custmer.update(msg));
    }
}

class Custmer1 implements Custmer {
    public void update(String msg) {
        System.out.println("1번 :" + msg);
    }
}

class Custmer2 implements Custmer {
    public void update(String msg) {
        System.out.println("2번 :" + msg);
    }
}

class Custmer3 implements Custmer {
    public void update(String msg) {
        System.out.println("3번 :" + msg);
    }
}
