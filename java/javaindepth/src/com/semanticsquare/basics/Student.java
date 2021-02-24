class Student {
    int id = 0;

    void compute() {
        int nextId = id + 1;
        long otherId = 2234567890L;
        System.out.println("otherId: " + otherId);
        System.out.println("Id: " + nextId);
    }

    public static void main(String[] args) {
        Student s = new Student();
        s.compute();
    }
}
