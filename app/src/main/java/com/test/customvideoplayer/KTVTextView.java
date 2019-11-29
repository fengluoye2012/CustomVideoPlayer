package com.test.customvideoplayer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.RectF;
import android.support.annotation.ColorInt;
import android.util.AttributeSet;
import android.view.View;

import com.blankj.utilcode.util.ColorUtils;
import com.blankj.utilcode.util.ConvertUtils;
import com.blankj.utilcode.util.LogUtils;

public class KTVTextView extends View {

    private Paint mPaint;
    /**
     * 文本的宽度
     */
    private float mTextWidth;

    private PorterDuffXfermode xformode;
    private String mText = "呼呼呼呼呼呼呼";

    /**
     * 文本颜色
     */
    private int textColor = ColorUtils.getColor(R.color.text_color_1);

    /**
     * 改变的颜色
     */
    private int changeTextColor = ColorUtils.getColor(R.color.text_color_3);

    /**
     * 改变文本的长度
     */
    private int changeWidth;

    /**
     * 是否允许改变颜色
     */
    private boolean changeColor = false;

    public KTVTextView(Context ctx) {
        this(ctx, null);
    }

    public KTVTextView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public KTVTextView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);

        mPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        xformode = new PorterDuffXfermode(PorterDuff.Mode.SRC_IN);
        initViewAndData();

        setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                changeWidth = 0;
                changeColor = true;
                changeTextWidth();
            }
        });
    }

    //没有处理宽高问题
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

    }

    public void initViewAndData() {
        mPaint.setColor(changeTextColor);
        mPaint.setTextSize(ConvertUtils.sp2px(16));
        mPaint.setStyle(Paint.Style.FILL_AND_STROKE);
        mPaint.setXfermode(null);
        mPaint.setTextAlign(Paint.Align.LEFT);

        //获取文本宽度
        mTextWidth = mPaint.measureText(mText);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        //创建Bitmap
        Bitmap srcBitmap = Bitmap.createBitmap(getWidth(), getHeight(), Bitmap.Config.ARGB_8888);
        Canvas srcCanvas = new Canvas(srcBitmap);

        //在Bitmap上绘制text文本
        RectF textRectF = new RectF(getPaddingLeft(), getPaddingTop(), getWidth(), getHeight());
        Paint.FontMetrics fontMetrics = mPaint.getFontMetrics();
        float baseline = (textRectF.bottom + textRectF.top - fontMetrics.bottom - fontMetrics.top) / 2;
        //下面这行是实现水平居中
        mPaint.setTextAlign(Paint.Align.LEFT);
        //在新建画板上绘制文本
        srcCanvas.drawText(mText, textRectF.left, baseline, mPaint);

        mPaint.setXfermode(xformode);
        mPaint.setColor(textColor);

        //根据宽度绘制矩形
        RectF rectF = new RectF(getPaddingLeft(), getPaddingTop(), changeWidth, getHeight());
        srcCanvas.drawRect(rectF, mPaint);

        //绘制Bitmap
        canvas.drawBitmap(srcBitmap, 0, 0, null);

        changeTextWidth();
    }

    public void changeTextWidth() {
        if (changeWidth < mTextWidth && changeColor) {
            initViewAndData();
            changeWidth += 10;
            postInvalidateDelayed(30);
        }
    }


    @Override
    protected void onAttachedToWindow() {
        super.onAttachedToWindow();
        LogUtils.i("onAttachedToWindow");
    }


    @Override
    protected void onDetachedFromWindow() {
        super.onDetachedFromWindow();

        LogUtils.i("onDetachedFromWindow");
    }

    /**
     * 设置text 颜色
     *
     * @param textColor
     */
    public void setTextColor(@ColorInt int textColor) {
        this.textColor = textColor;
        postInvalidate();
    }

    /**
     * 设置文本
     *
     * @param text
     */
    public void setText(String text) {
        this.mText = text;
    }

    /**
     * 设置 改变的字体颜色
     */
    public void setChangeColor(@ColorInt int changeTextColor) {
        this.changeTextColor = changeTextColor;
    }

}
