class Student {
    static int computeCount = 0;
    int baseId = 1000;
    String name;
    String gender;
    int age;
    long phone;
    double gpa;
    char degree;
    int[] scores;

    boolean international;
    double tuitionFees = 12000.0, internationalFees = 5000.0;

    void compute() {
        computeCount += 1;
        int id = baseId + computeCount;

        if (international) {
            tuitionFees += internationalFees;
        }

        System.out.println("\nid: " + id);
        System.out.println("age: " + age);
        System.out.println("name: " + name);
        System.out.println("gender: " + gender);
        System.out.println("phone: " + phone);
        System.out.println("tuitionFees: " + tuitionFees);
        System.out.println("computeCount: " + computeCount);
        System.out.print("Scores: ");
        for (int score: scores) {
            System.out.print(score + " ");
        }
        System.out.println();
        System.out.println("Num Exams: " + scores.length);
    }

    public static void main(String[] args) {
        Student student1 = new Student();
        student1.name = "John";
        student1.gender = "Male";
        student1.age = 18;
        student1.phone = 223_456_7890L;
        student1.gpa = 3.8;
        student1.degree = 'B';
        student1.international = false;
        student1.scores = new int[] {90, 98, 87};
        student1.scores[2] = 92;
        student1.compute();

        System.out.println("Student.computeCount: " + Student.computeCount);
    }
}
