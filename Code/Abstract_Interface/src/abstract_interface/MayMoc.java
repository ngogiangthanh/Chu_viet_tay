package abstract_interface;

public abstract class MayMoc {

    private String tenmaymoc;

    public abstract void setTenmaymoc(String tenmaymoc);

    public abstract String getTenmaymoc();
    public abstract String Show();


    public int Show1(){
        System.out.println(getTenmaymoc());
        return 0;
    }
}
