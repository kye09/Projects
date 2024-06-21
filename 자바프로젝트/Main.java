package POS;

public class Main {
    public static void 신라면_육개장_바나나우유_불고기김밥을_카드로_계산() {
        Pos 철수 = new Pos();

        철수.setFoodChoice(new Sinramyeon(new Yukgejang(new Bananamilk(new Bulgogi_Kimbap(new Basic())))));
        철수.food_choice();
        철수.setPay(new CreditCardCommand(new CreditPayPrint()));
        철수.usepay(10000);
        System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
    }

    public static void 육개장_야채김밥을_사고_10000원을_내면서_현금결제() {
        Pos 철수 = new Pos();
        철수.setFoodChoice(new Yukgejang(new Vege_Kimbap(new Basic())));
        철수.food_choice();
        철수.setPay(new CashCommand(new CashPayPrint()));
        철수.usepay(10000);
        System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
    }

    public static void 교통카드_충전() {
        Pos 철수 = new Pos();
        철수.setTransCharg(new TransCardCharging());
        철수.charging();
        철수.speak();
        System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
    }

    public static void 하이패스_충전() {
        Pos 철수 = new Pos();
        철수.setTransCharg(new HipassCardCharging());
        철수.charging();
        철수.speak();
        System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
    }

    public static void 손님1이_되어_POS기를_테스트한다() {
        PosUser user1 = new OneUser();
        user1.food_choice();
        user1.usepay(10000);
        System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
    }

    public static void 손님2가_되어_POS기를_테스트한다() {
        PosUser user2 = new TwoUser();
        user2.food_choice();
        user2.usepay(10000);
        System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
    }

    public static void 손님3명의_택배가_편의점에_도착_후_알림전송_후_2번이_택배를_가져가고_안가져간_인원에게_메시지전송() {
        DeliveryPos deliveryPos = new DeliveryPos();
        Custmer one = new Custmer1();
        Custmer two = new Custmer2();
        Custmer three = new Custmer3();

        deliveryPos.subcustmer(one);
        deliveryPos.subcustmer(two);
        deliveryPos.subcustmer(three);

        deliveryPos.arrival();
        System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
        deliveryPos.deletecustmer(two);
        deliveryPos.arrival();
        System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
    }

    public static void 김밥의_재고를_확인() {
        Pos 철수 = new Pos();
        철수.김밥재고();
    }

    public static void main(String[] args) {
        신라면_육개장_바나나우유_불고기김밥을_카드로_계산();
        육개장_야채김밥을_사고_10000원을_내면서_현금결제();
        교통카드_충전();
        하이패스_충전();
        손님1이_되어_POS기를_테스트한다();
        손님2가_되어_POS기를_테스트한다();
        손님3명의_택배가_편의점에_도착_후_알림전송_후_2번이_택배를_가져가고_안가져간_인원에게_메시지전송();
        김밥의_재고를_확인();
    }
}
