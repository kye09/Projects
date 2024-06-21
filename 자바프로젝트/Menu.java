package POS;

abstract public class Menu implements FoodChoice {
    int price;
    String name;

    public void TotalPrice() {
        System.out.println(getTotalPrice());
    }
}

class Bananamilk extends Menu {
    private FoodChoice foodChoice;
    private int price = 1400;
    private String name = "Bananamilk";

    public Bananamilk(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}

class Chocomilka extends Menu {
    private FoodChoice foodChoice;
    private int price = 1300;
    private String name = "Chocomilka";

    public Chocomilka(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}

class Coffeemilk extends Menu {
    private FoodChoice foodChoice;
    private int price = 1600;
    private String name = "Coffeemilk";

    public Coffeemilk(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}

class Bulgogi_Kimbap extends Menu {
    private FoodChoice foodChoice;
    private int price = 1200;
    private String name = "Bulgog_iKimbap";

    public Bulgogi_Kimbap(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}

class Tunamayo_Kimbap extends Menu {
    private FoodChoice foodChoice;
    private int price = 1200;
    private String name = "Tunamayo_Kimbap";

    public Tunamayo_Kimbap(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}

class Vege_Kimbap extends Menu {
    private FoodChoice foodChoice;
    private int price = 1000;
    private String name = "Vege_Kimbap";

    public Vege_Kimbap(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}

class JinRamyeon extends Menu {
    private FoodChoice foodChoice;
    private int price = 1500;
    private String name = "JinRamyeon";

    public JinRamyeon(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}

class Sinramyeon extends Menu {
    private FoodChoice foodChoice;
    private int price = 1500;
    private String name = "Sinramyeon";

    public Sinramyeon(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}

class Yukgejang extends Menu {
    private FoodChoice foodChoice;
    private int price = 800;
    private String name = "Yukgejang";

    public Yukgejang(FoodChoice foodChoice) {
        this.foodChoice = foodChoice;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public int getTotalPrice() {
        return foodChoice.getTotalPrice() + getPrice();
    }

    @Override
    public void foodPrint() {
        foodChoice.foodPrint();
        foodimfo();
    }

    public void foodimfo() {
        System.out.println(name + "     " + price);
    }
}