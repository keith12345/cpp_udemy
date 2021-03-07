class Students {
    public static void main(String[] args) {
        Student[] students = new Student[4];
        students[0] = new Student();
        students[0].name = "John";
        students[0].gender = "Male";
        students[0].age = 18;
        students[0].phone = 223_456_7890L;
        students[0].gpa = 3.8;
        students[0].degree = 'B';
        students[0].international = false;
        students[0].scores = new int[] {90, 98, 87};
        students[0].scores[2] = 92;
        students[0].compute();
    }
}
