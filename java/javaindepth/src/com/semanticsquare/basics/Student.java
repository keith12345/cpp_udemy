class Student {
    static int idCount = 0;
    int baseId = 1000;
    int id;
    String name;
    String gender;
    int age;
    long phone;
    double gpa;
    char degree;
    int[] scores;

    boolean international;
    double tuitionFees = 12000.0, internationalFees = 5000.0;

    Student() {
        Student.idCount += 1;
        this.id = baseId + idCount;
    }

    Student(String name, String gender, int age, long phone, double gpa, char degree, int... scores) {
        // non-international student constructor. 'this' can only appear once and must be the first statement
        this(name, gender, age, phone, gpa, degree, false, scores);
    }

    Student(String name, String gender, int age, long phone, double gpa, char degree, boolean international, int... scores) {
        idCount += 1;
        id = baseId + idCount;
        this.name = name;
        this.gender = gender;
        this.age = age;
        this.phone = phone;
        this.gpa = gpa;
        this.degree = degree;
        this.international = international;
        if (international) {
            this.tuitionFees += internationalFees;
        }
        this.scores = scores;
    }

    void display() {
        System.out.println("\nid: " + id);
        System.out.println("age: " + age);
        System.out.println("name: " + name);
        System.out.println("gender: " + gender);
        System.out.println("phone: " + phone);
        System.out.println("tuitionFees: " + tuitionFees);
        System.out.print("Scores: ");
        if (scores != null) {
            for (int score: scores) {
                System.out.print(score + " ");
            }
            System.out.println();
            System.out.println("Num Exams: " + scores.length);
        } else {
            System.out.println("No exams taken");
        }
    }

    public static void main(String[] args) {
        Student student1 = new Student("John", "Male", 18, 223_456_7890L, 3.8, 'B', false, new int[] {1, 2, 3});
        student1.display();
        Student student2 = new Student();
        student2.display();
        System.out.println("Student.idCount: " + Student.idCount);
    }
}
