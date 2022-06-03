package project;

interface MyPool {

    void execute(Runnable task);

    MyBlockingQueue shutdown();
}
