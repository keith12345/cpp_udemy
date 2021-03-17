class StudentTest {
    public static void main(String[] args) {
        Student student1 = new Student("John", "Male", 18, 223_456_7890L, 3.8, 'B', false, new int[] {1, 2, 3});
        student1.display();
        student1.updateName("Johnny");
        Student student2 = new Student();
        student2.display();
        System.out.println("Student.idCount: " + Student.idCount);
        int x = 12;
        int y = 9;
        System.out.println(Integer.toBinaryString(~x));
    }
}
