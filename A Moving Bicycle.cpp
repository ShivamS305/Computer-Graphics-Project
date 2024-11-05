#include <graphics.h>

#include <conio.h>

#include <string>

#include <math.h>

#include <windows.h> // Include for GetSystemMetrics



#define PI 3.14159265359



// Function to draw a yellow sun

void drawSun(int x, int y, int radius) {

    setcolor(YELLOW);

    setfillstyle(SOLID_FILL, YELLOW);

    circle(x, y, radius);    // Draw the circle for the sun

    floodfill(x, y, YELLOW);  // Fill the sun with yellow color

}



// Function to draw clouds

void drawCloud(int x, int y) {

    setcolor(WHITE);

    setfillstyle(SOLID_FILL, WHITE);



    // Draw the main body of the cloud

    fillellipse(x, y, 30, 20);

    fillellipse(x + 20, y - 10, 30, 20);

    fillellipse(x + 40, y, 30, 20);

    fillellipse(x + 10, y - 20, 30, 20);

    fillellipse(x + 30, y - 20, 30, 20);

}



// Function to draw rotating cycle wheel

void drawRotatingWheel(int x, int y, int radius, float angle, int color) {

    int numSpokes = 6; // Number of spokes in the wheel

    setcolor(color);

    circle(x, y, radius); // Draw the wheel (circle)



    // Draw spokes (rotating effect)

    for (int i = 0; i < numSpokes; i++) {

        float spokeAngle = angle + i * (2 * PI / numSpokes);

        int xEnd = x + radius * cos(spokeAngle);

        int yEnd = y + radius * sin(spokeAngle);

        line(x, y, xEnd, yEnd);

    }

}



// Function to draw a speed breaker as a small curve (top half of the circle)

void drawSpeedBreaker(int x, int y) {

    setcolor(WHITE);

    // Draw a triangular slope instead of an arc

    line(x - 30, y, x, y - 20);     // Left slope up

    line(x, y - 20, x + 30, y);     // Right slope down

}

int main() {

    int h = 0, page = 0;

    int circle1x = 100, circle2x = 250;

    int poly_upline = 150, poly_lowerline = 100, poly_leftline = 100, poly_rightline = 225;

    int handle_1 = 250, handle_2 = 225, handle_3 = 200;

    int sheet_1 = 150, sheet_2 = 145;

    int speed = 5;

    int n = 0;

    int Cycle_Color = 15; // Initial color of the cycle (white)

    float wheelAngle = 0.0f; // Angle for wheel rotation

    float rotationSpeed = 0.1f; // Controls how fast the wheels rotate



    // Jump mechanics

    bool isJumping = false;

    int jumpHeight = 150;   // Max height of the jump

    int jumpSpeed = 20;     // How fast the cycle jumps

    int jumpPeak = 0;       // Track jump position

    int baseY = 450;        // Base Y position of the cycle



    // Speed breaker position and size

    int speedBreakerX = 600;  // X position of the speed breaker

    int speedBreakerY = 500;  // Y position of the speed breaker (ground level)

    bool onSpeedBreaker = false;  // Check if the cycle is crossing the speed breaker

    int bumpLift = 30;  // How much the cycle lifts when crossing the bump



    DWORD screenwidth = GetSystemMetrics(SM_CXSCREEN);

    DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);

    initwindow(screenwidth, screenHeight, "Cool Programming Projects", -3);



    char s[30] = "Loading...";

    while (1) {

        if (n == 0) {

            setcolor(WHITE);

            rectangle(550 + 25, 320, 700 + 25, 340);

            for (int i = 0; i < 148; i++) {

                setcolor(GREEN);

                line(551 + i + 25, 321, 551 + i + 25, 339);

                setcolor(WHITE);

                outtextxy(615, 350, s);

                delay(10);

            }

            n++;  // Set to 1 after the loading bar completes

        }



        if (n != 0) {

            setactivepage(page);

            setvisualpage(1 - page);

        }

        cleardevice();

        setcolor(WHITE);

        line(0, 500, 1400, 500);  // Ground line



        // Draw the background (sky)

        setfillstyle(SOLID_FILL, BLUE);

        floodfill(0, 0, WHITE);

        bar(0, 0, screenwidth, 500);



        // Draw the sun at position (300, 100) with radius 50

        drawSun(300, 100, 50);



        // Draw clouds in different positions

        drawCloud(120, 100);

        drawCloud(420, 90);

        drawCloud(550, 110);

        drawCloud(650, 70);

        drawCloud(850, 100);

        drawCloud(950, 130);

        drawCloud(1150, 150);

        drawCloud(1250, 130);

        drawCloud(1350, 150);



        // Handle jumping

        if (isJumping) {

            if (jumpPeak < jumpHeight) {

                jumpPeak += jumpSpeed;  // Move up

            } else {

                isJumping = false;  // Start falling

            }

        } else if (jumpPeak > 0) {

            jumpPeak -= jumpSpeed;  // Fall down due to gravity

        }



        // Update the cycle's y-position based on jump

        int currentY = baseY - jumpPeak;



        // Check if the cycle is crossing the speed breaker

        if (circle2x >= speedBreakerX - 50 && circle1x <= speedBreakerX + 50) {

            onSpeedBreaker = true;

        } else {

            onSpeedBreaker = false;

        }



        // Adjust the cycle's y-position when crossing the speed breaker

        if (onSpeedBreaker && !isJumping) {

            if (circle1x >= speedBreakerX - 50 && circle1x <= speedBreakerX) {

                currentY -= bumpLift;  // Lift the front wheel

            } else if (circle2x >= speedBreakerX && circle2x <= speedBreakerX + 50) {

                currentY -= bumpLift / 2;  // Gradual lowering as the rear wheel crosses

            }

        }



        // Cycle tires (rotating wheels with the selected color)

        drawRotatingWheel(circle1x, currentY, 50, wheelAngle, Cycle_Color); // Left wheel

        drawRotatingWheel(circle2x, currentY, 50, wheelAngle, Cycle_Color); // Right wheel



        // Cycle body (with the selected color)

        setcolor(Cycle_Color);

        line(poly_lowerline, currentY, poly_lowerline + 75, currentY); // lower line of cycle

        line(poly_leftline, currentY, poly_leftline + 50, currentY - 60);   // left line of cycle

        line(poly_upline, currentY - 60, poly_upline + 75, currentY - 60);       // upper line of cycle

        line(poly_rightline, currentY - 60, poly_rightline - 50, currentY); // right line of cycle



        // Cycle handle (with the selected color)

        line(handle_1, currentY, handle_1 - 25, currentY - 60);

        line(handle_2, currentY - 60, handle_2 - 25, currentY - 110);

        line(handle_3, currentY - 110, handle_3 - 20, currentY - 110);



        // Cycle seat (with the selected color)

        line(sheet_1, currentY - 60, sheet_1, currentY - 70);

        line(sheet_2, currentY - 70, sheet_2 + 10, currentY - 70);



        // Draw the speed breaker on the road

        drawSpeedBreaker(speedBreakerX, speedBreakerY);



        // Move the cycle based on the arrow keys

        if (GetAsyncKeyState(VK_LEFT)) {

            circle1x -= speed;

            circle2x -= speed;

            poly_upline -= speed;

            poly_lowerline -= speed;

            poly_leftline -= speed;

            poly_rightline -= speed;

            handle_1 -= speed;

            handle_2 -= speed;

            handle_3 -= speed;

            sheet_1 -= speed;

            sheet_2 -= speed;



            // Rotate the wheels backward

            wheelAngle -= rotationSpeed;

        }



        if (GetAsyncKeyState(VK_RIGHT)) {

            circle1x += speed;

            circle2x += speed;

            poly_upline += speed;

            poly_lowerline += speed;

            poly_leftline += speed;

            poly_rightline += speed;

            handle_1 += speed;

            handle_2 += speed;

            handle_3 += speed;

            sheet_1 += speed;

            sheet_2 += speed;



            // Rotate the wheels forward

            wheelAngle += rotationSpeed;

        }



        if (GetAsyncKeyState(VK_UP) && !isJumping && jumpPeak == 0) {

            isJumping = true; // Start the jump

        }



        page = 1 - page;

    }



    getch();

    closegraph();

    return 0;

}
