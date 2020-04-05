# Red-Channel
A C++ Command Line Interface Video Capturing Program with the Following Features:


-> Simple Login Logout:
    The default Username is "user" and the password is "password".    (Not Included any Authentication text File just a Conditional Login)
    
 ![Screenshot (27)](https://user-images.githubusercontent.com/39043506/78473123-c63f7c00-775b-11ea-8ddb-70ca2aab37d1.png)
 
  With Correct Credentials the CLI lets the User into the Next Step:
 
 ![Screenshot (28)](https://user-images.githubusercontent.com/39043506/78473164-04d53680-775c-11ea-8b7c-10f192023b84.png)
  
  Select a Valid path to save your Video.

  It shows a set of options once a correct path is given. As Shown:

![Screenshot (29)](https://user-images.githubusercontent.com/39043506/78473211-875df600-775c-11ea-9c20-7788f10eadba.png)

-> Extracting Red Channel and applying Gaussian Blur:
  
  Selecting 1 Starts Recording the Video for 10 seconfs from which it seperates the Red Channel and apply Gaussian Blur (5x5) and finally store it in the provided path

  The Image Conversion of the Video Clip is as Follows

![RedChannel](https://user-images.githubusercontent.com/39043506/78473831-3b618000-7761-11ea-8f7a-8bb57109599e.jpg)

-> Showing the Videos Recorded in the CLI

  The Videos are uploaded in an orderly fashion. i.e, the Video Name is live(n).avi for the nth video Saved.

![Screenshot (30)](https://user-images.githubusercontent.com/39043506/78474893-a6ab5200-7761-11ea-8a22-73cfd40fd930.png)

There is a Windows exe file along with the source code in the repository. It is genersted by using Visual Studio Code.
