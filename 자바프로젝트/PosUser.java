package POS;

interface PosComponentFactory {
    void foodpay();

    void paymean();
}

abstract public class PosUser extends PosDevice implements PosComponentFactory {
    private Battery battery;
    private Window window;

    protected FoodChoice foodChoice;

    public PosUser() {
        foodpay();
        paymean();
    }

    public void food_choice() {
        foodChoice.foodPrint();
        System.out.print("합계:   ");
        foodChoice.TotalPrice();
    }

    protected CommandPay pay;

    public void usepay(Integer change) {
        pay.payment_ready(foodChoice.getTotalPrice(), change);
    }

}

class OneUser extends PosUser {
    public void foodpay() {
        foodChoice = new Yukgejang(new Yukgejang(new Bananamilk(new Vege_Kimbap(new Basic()))));
    }

    public void paymean() {
        pay = new CreditCardCommand(new CreditPayPrint());
    }
}

class TwoUser extends PosUser {
    public void foodpay() {
        foodChoice = new Sinramyeon(new Yukgejang(new JinRamyeon(new Tunamayo_Kimbap(new Basic()))));
    }

    public void paymean() {
        pay = new CashCommand(new CashPayPrint());
    }
}
