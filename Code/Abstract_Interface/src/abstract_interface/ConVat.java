package abstract_interface;

public abstract class ConVat {
    private String ten;
    private String id;

    public abstract void setId(String id);

    public abstract void setTen(String ten);

    public abstract String getId();

    public abstract String getTen();
    
    public void show(){
        System.out.println(getId());
        System.out.println(getTen());
    }
}
