
package POS;

public interface FoodChoice {
  public int getTotalPrice();

  public void TotalPrice();

  public void foodPrint();

}

class Basic implements FoodChoice {

  private int price = 0;

  @Override
  public int getTotalPrice() {
    return getPrice();
  }

  public int getPrice() {
    return price;
  }

  public void foodPrint() {
    System.out.println("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ");
  }

  public void TotalPrice() {
    System.out.println("");
  }

}

class Group {
  private Bananamilk 바나나우유;
  private Chocomilka 초코우유;
  private Coffeemilk 커피우유;
  private Bulgogi_Kimbap 불고기김밥;
  private Tunamayo_Kimbap 참치김밥;
  private Vege_Kimbap 야채김밥;
  private JinRamyeon 진라면;
  private Sinramyeon 신라면;
  private Yukgejang 육개장;

  public Group() {
    바나나우유 = new Bananamilk(new Basic());
    초코우유 = new Chocomilka(new Basic());
    커피우유 = new Coffeemilk(new Basic());
    불고기김밥 = new Bulgogi_Kimbap(new Basic());
    참치김밥 = new Tunamayo_Kimbap(new Basic());
    야채김밥 = new Vege_Kimbap(new Basic());
    진라면 = new JinRamyeon(new Basic());
    신라면 = new Sinramyeon(new Basic());
    육개장 = new Yukgejang(new Basic());
  }

  public void 전체메뉴() {
    바나나우유.foodimfo();
    초코우유.foodimfo();
    커피우유.foodimfo();
    불고기김밥.foodimfo();
    참치김밥.foodimfo();
    야채김밥.foodimfo();
    진라면.foodimfo();
    신라면.foodimfo();
    육개장.foodimfo();
  }

  public void 우유() {
    바나나우유.foodimfo();
    초코우유.foodimfo();
    커피우유.foodimfo();
  }

  public void 김밥() {
    불고기김밥.foodimfo();
    참치김밥.foodimfo();
    야채김밥.foodimfo();
  }

  public void 라면() {
    진라면.foodimfo();
    신라면.foodimfo();
    육개장.foodimfo();
  }
}