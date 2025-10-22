#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct {
    double x, y;
} Point;

int compareX(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x < p2->x) return -1;
    if (p1->x > p2->x) return 1;
    return 0;
}

int compareY(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->y < p2->y) return -1;
    if (p1->y > p2->y) return 1;
    return 0;
}

double dist(Point a, Point b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

double bruteForce(Point pts[], int n) {
    double minDist = DBL_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double d = dist(pts[i], pts[j]);
            if (d < minDist) minDist = d;
        }
    }
    return minDist;
}

double min(double a, double b) {
    return (a < b) ? a : b;
}

double stripClosest(Point strip[], int size, double d) {
    double minD = d;
    qsort(strip, size, sizeof(Point), compareY);
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < minD; j++) {
            double distance = dist(strip[i], strip[j]);
            if (distance < minD)
                minD = distance;
        }
    }
    return minD;
}

double closestUtil(Point pts[], int n) {
    if (n <= 3)
        return bruteForce(pts, n);

    int mid = n / 2;
    Point midPoint = pts[mid];

    double dl = closestUtil(pts, mid);
    double dr = closestUtil(pts + mid, n - mid);
    double d = min(dl, dr);

    Point *strip = (Point *)malloc(n * sizeof(Point));
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(pts[i].x - midPoint.x) < d)
            strip[j++] = pts[i];
    }

    double stripD = stripClosest(strip, j, d);
    free(strip);

    return min(d, stripD);
}

double closest(Point pts[], int n) {
    qsort(pts, n, sizeof(Point), compareX);
    return closestUtil(pts, n);
}

int main() {
    int n;
    while (scanf("%d", &n) == 1 && n > 0) {
        Point *pts = (Point *)malloc(n * sizeof(Point));
        for (int i = 0; i < n; i++) {
            scanf("%lf %lf", &pts[i].x, &pts[i].y);
        }

        double minDist = closest(pts, n);

        if (minDist >= 10000.0)
            printf("INFINITY\n");
        else
            printf("%.4lf\n", minDist);

        free(pts);
    }
    return 0;
}
