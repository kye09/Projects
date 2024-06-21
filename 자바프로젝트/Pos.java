package POS;

abstract class PosDevice {
}

abstract class Battery extends PosDevice {
}

abstract class Window extends PosDevice {
}

public class Pos extends PosDevice {
    private Battery battery;
    private Window window;

    private FoodChoice foodChoice;

    public void setFoodChoice(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public void food_choice() {
        foodChoice.foodPrint();
        System.out.print("합계:   ");
        foodChoice.TotalPrice();
    }

    private CommandPay pay;

    public void setPay(CommandPay pay) {
        this.pay = pay;
    }

    public void usepay(Integer change) {
        pay.payment_ready(foodChoice.getTotalPrice(), change);
    }

    private TransCharg transCharg;

    public void setTransCharg(TransCharg transCharg) {
        this.transCharg = transCharg;
    }

    public void charging() {
        transCharg.charging();
    }

    public void speak() {
        transCharg.speak();
    }

    Group group = new Group();

    public void 우유재고() {
        group.우유();

    }

    public void 김밥재고() {
        group.김밥();
    }

    public void 라면재고() {
        group.라면();
    }

    public void 전체재고() {
        group.전체메뉴();
    }

}