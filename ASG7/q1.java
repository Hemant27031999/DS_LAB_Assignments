import java.util.*;
import java.lang.*;
import java.io.*;


class Point
{   double x, y;
 
    Point(){}
 
    Point(double p, double q){
        x = p;
        y = q;
    }
}
 
public class q1{

    public static boolean segment_is_on(Point p, Point q, Point r)
    {
        if (q.x <= Math.max(p.x, r.x) && q.x >= Math.min(p.x, r.x)
                && q.y <= Math.max(p.y, r.y) && q.y >= Math.min(p.y, r.y))
            return true;
        return false;
    }
 
    public static double orientation_of_polygon(Point p, Point q, Point r)
    {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
 
        if (val == 0)
            return 0;
        return (val > 0) ? 1 : 2;
    }
 
    public static boolean doing_intersection(Point p1, Point q1, Point p2, Point q2)
    {
 
        double o1 = orientation_of_polygon(p1, q1, p2);
        double o2 = orientation_of_polygon(p1, q1, q2);
        double o3 = orientation_of_polygon(p2, q2, p1);
        double o4 = orientation_of_polygon(p2, q2, q1);
 
        if (o1 != o2 && o3 != o4)
            return true;
 
        if (o1 == 0 && segment_is_on(p1, p2, q1))
            return true;
 
        if (o2 == 0 && segment_is_on(p1, q2, q1))
            return true;
 
        if (o3 == 0 && segment_is_on(p2, p1, q2))
            return true;
 
        if (o4 == 0 && segment_is_on(p2, q1, q2))
            return true;
 
        return false;
    }
 
    public static boolean on_being_Inside(Point polygon[], int n, Point p)
    {
        double INF = 10000;
        if (n < 3)
            return false;
 
        Point extreme = new Point(INF, p.y);
 
        int count = 0, i = 0;
        do
        {
            int next = (i + 1) % n;
            if (doing_intersection(polygon[i], polygon[next], p, extreme))
            {
                if (orientation_of_polygon(polygon[i], p, polygon[next]) == 0)
                    return segment_is_on(polygon[i], p, polygon[next]);
 
                count++;
            }
            i = next;
        } while (i != 0);
 
        return (count & 1) == 1 ? true : false;
    }
 
    public static void main(String args[])
    {
        Scanner sc=new Scanner(System.in);

        System.out.print("Enter the coordinates of Rectangle (Bottom Left, Top Right) : ");

        Point r1=new Point();
        Point r2=new Point();
        r1.x=sc.nextDouble();
        r1.y=sc.nextDouble();
        dos();
        r2.x=sc.nextDouble();
        r2.y=sc.nextDouble();
                
                
        System.out.println("Enter the coordinates of Second Polygon : ");
         Point l1=new Point();
         Point l2=new Point();
         Point l3=new Point();
         Point l4=new Point();
         Point l5=new Point();
         Point l6=new Point();

        l1.x=sc.nextDouble();
        l1.y=sc.nextDouble();
        l2.x=sc.nextDouble();
        l2.y=sc.nextDouble();
        l3.x=sc.nextDouble();
        l3.y=sc.nextDouble();
        l4.x=sc.nextDouble();
        l4.y=sc.nextDouble();
        l5.x=sc.nextDouble();
        l5.y=sc.nextDouble();
        l6.x=sc.nextDouble();
        l6.y=sc.nextDouble();
        dos();


        Point polygon1[] = { new Point(r1.x, r1.y), new Point(r2.x, r1.y),
            new Point(r2.x, r2.y), new Point(r1.x, r2.y) }; 
            
            int n1= 4;

        dos();

        Point polygon2[] = { new Point(l1.x, l1.y), new Point(l2.x, l2.y),
            new Point(l3.x, l3.y), new Point(l4.x, l4.y),new Point(l5.x, l5.y),new Point(l6.x, l6.y) };

                int n2=6;

                System.out.println("Enter the number of points to be checked : ");
                int np=sc.nextInt();
                Point p = new Point();

                for(double i=0;i<np;i++)
                {

                    
                    p.x=sc.nextDouble();
                    p.y=sc.nextDouble();
                    boolean rect=on_being_Inside(polygon1, n1, p);
                    boolean lshape=on_being_Inside(polygon1, n1, p);

                    if(rect==true && lshape==true)
                    {
                        System.out.print("("+p.x+","+p.y+")"+"\t");
            
                    }

                }
                dos();
                System.out.println();
    }
    public static void dos(){}
}
