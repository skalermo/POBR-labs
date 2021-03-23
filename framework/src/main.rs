extern crate opencv;
use opencv::{types, imgcodecs, highgui, Error};
use opencv::core::{Mat, Rect, MatTrait, Vec3b, CV_8UC3, Scalar};

fn perform(mut img: Mat) -> Result<Mat, Error> {
    match img.channels()? {
        1 => {
            for i in 0..img.rows() {
                for j in 0..img.cols() {
                    *img.at_2d_mut(i, j)? = (img.at_2d(i, j)? / 32) * 32;
                }
            }
        },
        3 => {
            for i in 0..img.rows() {
                for j in 0..img.cols() {
                    let mut pixel = img.at_2d::<Vec3b>(i, j)?.0;
                    pixel[0] = pixel[0] / 32 * 32;
                    pixel[1] = pixel[1] / 32 * 32;
                    pixel[2] = pixel[2] / 32 * 32;
                    *img.at_2d_mut::<Vec3b>(i, j)? = Vec3b::from(pixel);
                }
            }
        },
        _ => unreachable!(),
    };
    Ok(img)
}

fn select_max(img: &Mat) -> Result<Mat, Error> {
    let mut res= Mat::new_rows_cols_with_default(img.rows(), img.cols(),
                                                 CV_8UC3, Scalar::default())?;
    match img.channels()? {
        3 => {
            for i in 0..img.rows() {
                for j in 0..img.cols() {
                    let pixel = img.at_2d::<Vec3b>(i, j)?.0;
                    let mut sel = if pixel[0] < pixel[1] { 1 } else { 0 };
                    sel = if pixel[sel] < pixel[2] {2} else {sel};
                    *res.at_2d_mut(i, j)? = Vec3b::from(
                        [if sel == 0 {255} else {0},
                            if sel == 1 {255} else {0},
                            if sel == 2 {255} else {0},]
                    )
                }
            }
        },
        _ => unreachable!(),
    }
    Ok(res)
}

fn main() -> Result<(), Error> {
    println!("Start...");
    let image = imgcodecs::imread("Lena.png", 1)?;
    let mut image2 = Mat::roi(&image, Rect::new(100, 100, 100, 100))?;
    image2 = perform(image2)?;
    let max = select_max(&image)?;
    highgui::imshow("Lena", &image)?;
    highgui::imshow("Max", &max)?;
    println!("{} {}", image2.is_continuous()?, max.is_continuous()?);
    imgcodecs::imwrite("Max.png", &max, &types::VectorOfi32::new())?;
    highgui::wait_key(0)?;
    Ok(())
}


