class $HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello, world!!");
    }
}

// Apparently you don't normally put multiple classes in a single file
// but this is interesting as it shows that each classes gets its own
// class file when compiled.

class GoodbyeWorld {
    public static void main(String[] args) {
        System.out.println("Goodbye, bitter world!!");
    }
}
