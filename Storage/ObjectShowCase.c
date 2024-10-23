#define MAX_length 1024
// Base "class" Object
typedef struct {
    char name[MAX_length];
    void (*display)(void*);  // Function pointer for polymorphic behavior
} Object;

// "Derived class" Circle
typedef struct {
    Object base;
    double radius;
} Circle;

// "Derived class" Rectangle
typedef struct {
    Object base;
    double width;
    double height;
} Rectangle;

// Display function for Circle
void display_circle(void* obj) {
    Circle* circle = (Circle*)obj;
    printf("Circle: %s, Radius: %.2f\n", circle->base.name, circle->radius);
}

// Display function for Rectangle
void display_rectangle(void* obj) {
    Rectangle* rect = (Rectangle*)obj;
    printf("Rectangle: %s, Width: %.2f, Height: %.2f\n", rect->base.name, rect->width, rect->height);
}