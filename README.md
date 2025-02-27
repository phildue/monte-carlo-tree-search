# uniqFEED Coding Challenge for C++ Software Engineers

Thank you for taking our coding challenge!  Please choose **one** of the following two problems to solve.

  * Create a branch for your changes & answers.
  * When done, commit your changes, push the commits & send us a pull request.

See also: https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request

We expect to receive your answer within 24 hours from when this invitation was sent.  If you run into any difficulties, or have any questions please don't hesitate to ask.

## Challenge 1:  Task Pipline

You are building an image processing system and you have a prototype:

```C++
    // Some class that contains an image - the internals of the class are not relevant.
    class Image;

    // Get an image from a device, write to a device.
    Image getImageFromDevice();
    void outputImageToDevice(Image);


    // The details of these functions are not important.
    // An Image comes in, a processed image goes out
    Image applyTransform0(Image);
    Image applyTransform1(Image);
    Image applyTransform2(Image);


    void processImages()
    {
        while(true)
        {
			auto image = getImageFromDevice();

			image = applyTransform0(image);
			image = applyTransform1(image);
			image = applyTransform2(image);

			outputImageToDevice(image);
        }
    }
```

Now you realize you will need to parallelize this pipeline to improve the throughput.  Your goal is to make a pipeline class which parallelizes the execution of the transformations.  We want n threads running n transformations in parallel, with each image undergoing the transformation in the proper sequence.  You can assume that the number of transformations is not significantly more than the number of cores on the system.

Your class should not need to know anything about the transformations it is applying.  It should be easy for a user of your class to add, remove, or reorder transformatoins.  We are looking for a simple interface like the following:

   ```C++
       Pipeline pipe;

       pipe.addStage(getImageFromDevice);
       pipe.addStage(applyTransform0);
       pipe.addStage(applyTransform1);
       pipe.addStage(outputImageToDevice);

       pipe.run();
   ```

So in the code above, we create a pipeline with two transformatoin stages, as well as stages for getting and outputting images.  During execution an image should be passed from ``getImageFromDevice`` to ``transform0`` to ``transform1`` to ``outputImageToDevice``.   Each stage should execute on a separate thread from the others.  So  ``transform1`` should execute on a seperate thread from ``transform0`` while ``transform0`` moves on the next image in the queue.  I.E. you want to process the sequence in a parallelized pipeline where every stage(transform) in the pipeline runs on its own thread.  There are no guarentees on how long each stage might take.

Please implement such a pipeline in  C++.

## Challenge 2: Linear Interpolation

There are three parts to this problem, make one file per part (feel free to copy-paste from previous parts).  Answers to the prose questions should go in the comments for that part.

### Part 1:
![linear interpolation plot](interpolation_plot_inv.png "linear interpolation plot")

Make a class that provides linear interpolation.  Your class should provide the following:
 - an arbitrary amount of values can be inserted in any order
 - values can be queried for any point in time, by performing a linear interpolation of two surrounding values.

#### Provide the following public interface:
```
 void add_value(float time, float value);
 float get_value_for_time(float time) const;
```

#### corner-cases:
 - in case no values were inserted yet -> return 0
 - queried time is before first value -> return first value
 - queried time is after last value -> return last value

#### use this code to drive your class:

```
int main()
{
    YourClass foo;

    // add some values in arbitrary order
    foo.add_value(8.88f, 99.f);
    foo.add_value(0.3f, 2.f);
    foo.add_value(17.3f, 42.f);
    foo.add_value(4.f, 23.f);

    // query for some arbitrary points in time
    std::cout << "0.0 -> " << foo.get_value_for_time(0.f) << std::endl;
    std::cout << "1.23 -> " << foo.get_value_for_time(1.23f) << std::endl;
    std::cout << "6.66 -> " << foo.get_value_for_time(6.66f) << std::endl;
    std::cout << "13.0 -> " << foo.get_value_for_time(13.f) << std::endl;
    std::cout << "39.0 -> " << foo.get_value_for_time(39.f) << std::endl;

    return 0;
}
```
should print:

```
0.0 -> 2
1.23 -> 7.27838
6.66 -> 64.4262
13.0 -> 71.1093
39.0 -> 42
```

#### complexities
 - what are the complexities for the two operations in your solution?
 - what's the optimum complexity?

### Part 2 : support additional interpolations

The solution must be extended to cover different types of interpolation.  It should be possible to switch between interpolations without re-adding values (i.e. without duplicating the data stored).  Extend your solution to support [smooth hermite-interpolation](https://en.wikipedia.org/wiki/Smoothstep)

```
f(x) = 3x^2 - 2x^3
```
![smoothstep interpolation plot](interpolation_plot_smoothstep_inv.png "smoothstep interpolation plot")


### Part 3 : support other data types
The API above operates on float-data for the values.
 - Extend the solution to support double-precision as well.
 - How would you support vector types?
 - What are the formal requirements in C++ for data-types you could support?
