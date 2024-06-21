package POS;

abstract public class TransCharg {
    protected abstract void charging_start();

    protected abstract void charging_ing();

    protected abstract void charging_end();

    public void charging() {
        charging_start();
        charging_ing();
        charging_end();
    }

    public void speak() {
        System.out.println("띠링 신호을 말하다.");
    }

}

class TransCardCharging extends TransCharg {
    protected void charging_start() {
        System.out.println("교통카드를 올려놔주세요");
    }

    protected void charging_ing() {
        System.out.println("교통카드를 충전 중입니다.");
    }

    protected void charging_end() {
        System.out.println("교통카드 충전이 완료됐습니다.");
    }
}

class HipassCardCharging extends TransCharg {
    protected void charging_start() {
        System.out.println("하이패스 카드를 올려놔주세요");
    }

    protected void charging_ing() {
        System.out.println("하이패스 카드 충전 중입니다.");
    }

    protected void charging_end() {
        System.out.println("하이패스 카드가 충전 완료됐습니다.");
    }
}
