package com.semanticsquare.basics;


public class Student {
    private static int idCount = 0;
    private int baseId = 1000;
    private int id;
    private String name;
    private String gender;
    private int age;
    private long phone;
    private double gpa;
    private char degree;
    private int[] scores;

    private boolean international;
    private double tuitionFees = 12000.0, internationalFees = 5000.0;

    public Student() {
        Student.idCount += 1;
        this.id = baseId + idCount;
    }

    public Student(String name, String gender, int age, long phone, double gpa, char degree, int... scores) {
        // non-international student constructor. 'this' can only appear once
        // when calling another constructor and must be the first statement
        this(name, gender, age, phone, gpa, degree, false, scores);
    }

    public Student(String name, String gender, int age, long phone, double gpa, char degree, boolean international, int... scores) {
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

    public boolean setId(int id) {
        if (id < 1000) {
            throw new IllegalArgumentException("Id is not greater than 1000");
        } else {
            this.id = id;
        }
        return true;
    }

    public boolean setName(String name) {
        System.out.printf("Updating name of Student %d from %s to %s.\n", this.id, this.name, name);
        this.name = name;
        return true;
    }

    public boolean setGender(String gender) {
        if (gender.equals("male") || gender.equals("female") || gender.equals("transgender")) {
            throw new IllegalArgumentException("Gender not in 'male', 'female', 'transgender'");
        } else {
            this.gender = gender;
        }
        return true;
    }

    public String getName() {
        return this.name;
    }

    public void display() {
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
        Student s = new Student();
        s.display();
    }
}
