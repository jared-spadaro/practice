#include "data.h"
#include "vector_math.h"
#include "collisions.h"
#include "cast.h"
#include <stdio.h>
#include <math.h>

double distance (struct point p1, struct point p2)
{
   return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+(p1.z-p2.z)*(p1.z-p2.z));
}

int nearest_eye (struct point const input[],struct point eye,int size)
{
   int i;
   int index_nearest = 0;
   for(i=0;i<size;i++)
   {
      if(distance(eye,input[index_nearest]) > distance(eye,input[i]))
      {
         index_nearest = i;
      }
   }
   return index_nearest;
}







struct color cast_ray (struct ray r,struct sphere spheres[],int num_spheres,struct color ambient,struct light l,struct point eye)
{
   
   struct color sphere_color;
   int intersect;
   int index_nearest;
   struct sphere hit_spheres[10000];
   struct point intersection_points[10000];
   
   struct vector N;
   struct point new_p;
   struct vector L_dir;
   double dot;
   struct ray diffuse_ray;   
   int light_intersect;
   int light_index_nearest;
   struct sphere light_hit_spheres[10000];
   struct point light_intersection_points[10000];
   
   struct vector ref_vector;
   struct vector v_dir;
   double spec_intensity;

   intersect = find_intersection_points(spheres,num_spheres,r,hit_spheres,intersection_points);

   if (intersect > 0)
   {
	   index_nearest = nearest_eye(intersection_points,r.p,intersect);
   
	   N = sphere_normal_at_point(hit_spheres[index_nearest],intersection_points[index_nearest]);
	   new_p = translate_point(intersection_points[index_nearest],scale_vector(N,0.01));
	   L_dir = normalize_vector(difference_point(l.p,new_p));
	   dot = dot_vector(N,L_dir);
	   diffuse_ray = create_ray(new_p,L_dir);

       light_intersect = find_intersection_points(spheres,num_spheres,diffuse_ray,light_hit_spheres,light_intersection_points);
	   
	   ref_vector = difference_vector(L_dir,scale_vector(N,(2*dot)));
	   v_dir = normalize_vector(difference_point(new_p,eye));
	   spec_intensity = dot_vector(ref_vector,v_dir);
	   
	   if (light_intersect > 0) 
	   {
              light_index_nearest = nearest_eye(light_intersection_points,diffuse_ray.p,light_intersect);

	      if(distance(new_p,light_intersection_points[light_index_nearest])<distance(new_p,l.p))
	      {
	          dot=0;
	      }
           }
	   
	   double diff = dot*hit_spheres[index_nearest].f.diffuse;
   

	   if(dot > 0 && spec_intensity>0)
	   {
          sphere_color = hit_spheres[index_nearest].c;
	      sphere_color.r = sphere_color.r * ((ambient.r * hit_spheres[index_nearest].f.ambient)+(l.color.r*diff))+(l.color.r*hit_spheres[index_nearest].f.specular*pow((spec_intensity),(1/hit_spheres[index_nearest].f.roughness)));
	      sphere_color.g = sphere_color.g * ((ambient.g * hit_spheres[index_nearest].f.ambient)+(l.color.g*diff))+(l.color.g*hit_spheres[index_nearest].f.specular*pow((spec_intensity),(1/hit_spheres[index_nearest].f.roughness)));
	      sphere_color.b = sphere_color.b * ((ambient.b * hit_spheres[index_nearest].f.ambient)+(l.color.b*diff))+(l.color.b*hit_spheres[index_nearest].f.specular*pow((spec_intensity),(1/hit_spheres[index_nearest].f.roughness)));
	   }
	   else if (dot>0)
	   {
	      sphere_color = hit_spheres[index_nearest].c;
	      sphere_color.r = sphere_color.r * ((ambient.r * hit_spheres[index_nearest].f.ambient)+(l.color.r*diff));
	      sphere_color.g = sphere_color.g * ((ambient.g * hit_spheres[index_nearest].f.ambient)+(l.color.g*diff));
	      sphere_color.b = sphere_color.b * ((ambient.b * hit_spheres[index_nearest].f.ambient)+(l.color.b*diff));
       }
	   else
	   {
	      sphere_color = hit_spheres[index_nearest].c;
	      sphere_color.r = sphere_color.r * ((ambient.r * hit_spheres[index_nearest].f.ambient));
	      sphere_color.g = sphere_color.g * ((ambient.g * hit_spheres[index_nearest].f.ambient));
	      sphere_color.b = sphere_color.b * ((ambient.b * hit_spheres[index_nearest].f.ambient)); 
       }
   }
   else
   {
       sphere_color = create_color(1.0,1.0,1.0);
   }
  
   return sphere_color;
}




int color_scale (double x)
{
   if(x>1.0)
   {
      x=1.0;
   }  
   return x * 255;
}




void cast_all_rays (double min_x,double max_x,double min_y,double 
max_y,int width,int height,struct point eye,struct sphere spheres[],int 
num_spheres,struct color ambient,struct light l)
{
   struct ray r;
   struct vector v;
   struct color intersect;
   
   int i;
   int j;
   
   printf("P3\n");
   printf("%d %d\n",width,height);
   printf("255\n");
   
   for(i=0;i<height;i++)
   {
      
      for(j=0;j<width;j++)
      {
           
         v = difference_point(create_point(min_x+((double)j*(max_x-min_x)/(double) width),max_y-((double) i*(max_y-min_y)/(double) height),0),eye);
         r = create_ray(eye,v);
         intersect = cast_ray(r,spheres,num_spheres,ambient,l,eye);
         
         
         printf("%d\n",color_scale(intersect.r));
         printf("%d\n",color_scale(intersect.g));
         printf("%d\n",color_scale(intersect.b));
         
      }
   }
}




