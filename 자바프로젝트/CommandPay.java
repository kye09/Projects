package POS;

public interface CommandPay {
    public void payment_ready(Integer money, Integer change);
}

class CreditPayPrint {
    public void pay(Integer money, Integer change) {
        System.out.println(money + "이 결제되었습니다.");
    }
}

class CashPayPrint {
    public void cashpay(Integer money, Integer change) {
        System.out.println(money + "이 결제되었습니다.");
        System.out.println("거스름돈은 " + (change - money) + "원입니다");
    }
}

class CommandMean {
    private CommandPay commandpay;

    public CommandMean(CommandPay commandpay) {
        setCommand(commandpay);
    }

    public void setCommand(CommandPay commandpay) {
        this.commandpay = commandpay;
    }

    public void payment_start(Integer money, Integer change) {
        commandpay.payment_ready(money, change);
    }
}

class CreditCardCommand implements CommandPay {
    private CreditPayPrint creditpayprint;

    public CreditCardCommand(CreditPayPrint creditpayprint) {
        this.creditpayprint = creditpayprint;
    }

    public void payment_ready(Integer money, Integer change) {
        creditpayprint.pay(money, change);
    }
}

class GiftCardCommand implements CommandPay {
    private CreditPayPrint creditpayprint;

    public GiftCardCommand(CreditPayPrint creditpayprint) {
        this.creditpayprint = creditpayprint;
    }

    public void payment_ready(Integer money, Integer change) {
        creditpayprint.pay(money, change);
    }
}

class CashCommand implements CommandPay {
    private CashPayPrint cashPayPrint;

    public CashCommand(CashPayPrint cashPayPrint) {
        this.cashPayPrint = cashPayPrint;
    }

    public void payment_ready(Integer money, Integer change) {
        cashPayPrint.cashpay(money, change);
    }
}

class TransCardCommand implements CommandPay {
    private CreditPayPrint creditpayprint;

    public TransCardCommand(CreditPayPrint creditpayprint) {
        this.creditpayprint = creditpayprint;
    }

    public void payment_ready(Integer money, Integer change) {
        creditpayprint.pay(money, change);
    }
}