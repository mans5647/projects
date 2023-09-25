package com.example.datetime;

import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.AppCompatButton;
import androidx.constraintlayout.widget.ConstraintLayout;

import android.app.Dialog;
import android.os.Bundle;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.RelativeLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.sql.Array;
import java.sql.Date;
import java.sql.Time;
import java.time.DayOfWeek;
import java.util.Calendar;
import java.util.List;

public class MainActivity extends AppCompatActivity {


    EditText dateT, timeT;
    ImageButton DateBut, TimeBut;
    Button apply;

    Dialog dialog;

    String prettyDay, prettyMonth, prettyYear, prettyHour, prettyMin;
    Spinner Days, Months, Years, Hrs, Mins;
    
    Button setDateButton, yBut, nBut, closeButSuccessWindow;
    
    TextView H, M, OrderText;
    
    AppCompatButton apply_time;

    String monthName;
    final String Alert = "Do you really continue on ";
    final char QMark = '?';
    String getMonthName()
    {
        String local = new String();
        int monthInNumber = Integer.valueOf(prettyMonth);
        switch (monthInNumber)
        {
            case 1:
                local = "January";
                break;
            case 2:
                local = "February";
                break;
            case 3:
                local = "March";
                break;
                case 4:
                local = "April";
                break;
            case 5:
            local = "May";
            break;case 6:
            local = "June";
            break;case 7:
            local = "July";
            break;case 8:
            local = "August";
            break;case 9:
            local = "September";
            break;case 10:
            local = "October";
            break;case 11:
            local = "November";
            break;case 12:
            local = "December";
            break;
            default:
                local = "(Unknown month)";
        }


        return local;
    }

    String getFormattedTime()
    {
        int local_hour = Integer.valueOf(prettyHour);
        String hourAmPm = (local_hour <= 12 && local_hour >= 0) ? "(AM)" : "(PM)";
        return new String(prettyHour + ":" + prettyMin + ' ' + hourAmPm);
    }

    String getFormattedDateTime()
    {
        return new String(prettyDay + ' ' + getMonthName() + ' ' + prettyYear + ' ' + getFormattedTime());
    }


    String getFormattedQuestion()
    {
        return new String(Alert + getFormattedDateTime() + QMark);
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        dateT = findViewById(R.id.dateText);
        timeT = findViewById(R.id.timeText);
        DateBut = findViewById(R.id.selDate);

        TimeBut = findViewById(R.id.selTime);

        apply = findViewById(R.id.applybt);


        prettyDay = GetDefaultDay(); // not current!
        prettyMonth = GetDefaultMonth(); // not current!
        prettyYear = GetDefaultYear(); // not current!

        dateT.setText(null);
        timeT.setText(null);

        TimeBut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                LayoutInflater Inf = (LayoutInflater) getSystemService(LAYOUT_INFLATER_SERVICE);

                View pop = Inf.inflate(R.layout.time_picker, null);

                int width = LinearLayout.LayoutParams.WRAP_CONTENT;
                int height = LinearLayout.LayoutParams.WRAP_CONTENT;
                boolean focusable = true; // lets taps outside the popup also dismiss it
                final PopupWindow popupWindow = new PopupWindow(pop, width, height, focusable);

                Hrs = pop.findViewById(R.id.spH);
                Mins = pop.findViewById(R.id.spM);

                H = pop.findViewById(R.id.h_setter);
                M = pop.findViewById(R.id.m_setter);
                apply_time = pop.findViewById(R.id.applyTime);


                popupWindow.showAtLocation(view, Gravity.CENTER, 0, 0);

                FillTimeQualifiers();

                apply_time.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {

                        final String format = prettyHour + ":" + prettyMin;
                        timeT.setText(format);


                    }
                });


                Hrs.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
                    @Override
                    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                        prettyHour = Hrs.getSelectedItem().toString();
                        H.setText(prettyHour);
                    }

                    @Override
                    public void onNothingSelected(AdapterView<?> adapterView) {
                        prettyHour = "00";
                        H.setText(prettyHour);
                    }
                });

                Mins.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
                    @Override
                    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                        prettyMin = Mins.getSelectedItem().toString();
                        M.setText(prettyMin);

                    }

                    @Override
                    public void onNothingSelected(AdapterView<?> adapterView) {
                        prettyMin = "00";
                        M.setText(prettyMin);
                    }
                });

            }
        });




    }


    public void GetMsg()
    {
        Toast.makeText(this, "Hello", Toast.LENGTH_SHORT).show();
    }


    public void show(View v)
    {
        LayoutInflater Inf = (LayoutInflater) getSystemService(LAYOUT_INFLATER_SERVICE);

        View pop = Inf.inflate(R.layout.datetimepicker, null);

        int width = LinearLayout.LayoutParams.WRAP_CONTENT;
        int height = LinearLayout.LayoutParams.WRAP_CONTENT;
        boolean focusable = true; // lets taps outside the popup also dismiss it
        final PopupWindow popupWindow = new PopupWindow(pop, width, height, focusable);

        Days = pop.findViewById(R.id.day);
        Months = pop.findViewById(R.id.month);
        Years = pop.findViewById(R.id.year);

        FillSpinnersWithValues();


        Days.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                prettyDay = Days.getSelectedItem().toString();

            }
            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
                prettyDay = GetDefaultDay();
            }
        });



        Months.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                prettyMonth = Months.getSelectedItem().toString();
            }
            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
                prettyMonth = GetDefaultMonth();
            }
        });


        Years.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {
                prettyYear = Years.getSelectedItem().toString();
            }
            @Override
            public void onNothingSelected(AdapterView<?> adapterView) {
                prettyYear = GetDefaultYear();
            }
        });






        popupWindow.showAtLocation(v, Gravity.CENTER, 0, 0);


        setDateButton = pop.findViewById(R.id.applyDate);

        setDateButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                final String format_msg = prettyDay + "/" + prettyMonth + "/" + prettyYear;
                dateT.setText(format_msg);
            }
        });

    }

    public void FillSpinnersWithValues()
    {
        int CurrentYear = Calendar.getInstance().get(Calendar.YEAR);
        int CurrentDay = Calendar.getInstance().get(Calendar.DAY_OF_WEEK);
        int CurrentMonth = Calendar.getInstance().get(Calendar.MONTH);

        String[] days = new String[31];
        String[] months = new String[12];
        String[] years = new String[2090];
        int minYear = 2002;
        for (int i = 0; i < days.length; i++) days[i] = Integer.toString(i + 1);
        for (int i = 0; i < months.length; i++) months[i] = Integer.toString(i + 1);
        for (int i = 0; i < years.length; i++) years[i] = Integer.toString(minYear++);

        ArrayAdapter<String> textRepDays = new ArrayAdapter<String>(this, androidx.appcompat.R.layout.support_simple_spinner_dropdown_item, days);
        ArrayAdapter<String> textRepMonths = new ArrayAdapter<String>(this, androidx.appcompat.R.layout.support_simple_spinner_dropdown_item, months);
        ArrayAdapter<String> textRepYears = new ArrayAdapter<String>(this, androidx.appcompat.R.layout.support_simple_spinner_dropdown_item, years);

        Days.setAdapter(textRepDays);
        Months.setAdapter(textRepMonths);
        Years.setAdapter(textRepYears);


    }

    private void FillTimeQualifiers()
    {
        String[] maxHours = new String[24];
        String[] maxMinutes = new String[60];
        for (int i = 0; i < 24; i++) maxHours[i] = Integer.toString(i);
        for (int i = 0; i < 60; i++) maxMinutes[i] = Integer.toString(i);

        ArrayAdapter<String> adapter_for_h = new ArrayAdapter<String>(this, androidx.constraintlayout.widget.R.layout.support_simple_spinner_dropdown_item, maxHours);
        ArrayAdapter<String> adapter_for_m = new ArrayAdapter<String>(this, com.google.android.material.R.layout.support_simple_spinner_dropdown_item, maxMinutes);

        Hrs.setAdapter(adapter_for_h);
        Mins.setAdapter(adapter_for_m);


    }



    public void checkout(View v)
    {
        String datetext = dateT.getText().toString();
        String timetext = timeT.getText().toString();
        if (datetext.length() != 0 && timetext.length() != 0)
        {
            ShowDialogWindow(v);
        }
    }


    private void ShowDialogWindow(View v)
    {
        LayoutInflater Inf = (LayoutInflater) getSystemService(LAYOUT_INFLATER_SERVICE);

        View pop = Inf.inflate(R.layout.dialog_window, null);

        int width = LinearLayout.LayoutParams.WRAP_CONTENT;
        int height = LinearLayout.LayoutParams.WRAP_CONTENT;
        boolean focusable = true; // lets taps outside the popup also dismiss it
        final PopupWindow popupWindow = new PopupWindow(pop, width, height, focusable);

        OrderText = pop.findViewById(R.id.orderDetailsText);

        yBut = pop.findViewById(R.id.yesBut);
        nBut = pop.findViewById(R.id.noBut);

        popupWindow.showAtLocation(v, Gravity.CENTER, 0, 0);

        OrderText.setText(getFormattedQuestion());

        yBut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                popupWindow.dismiss();
                ShowInfoWindow(v);
            }
        });

        nBut.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                popupWindow.dismiss();
            }
        });

    }

    private void ShowInfoWindow(View v)
    {
        LayoutInflater Inf = (LayoutInflater) getSystemService(LAYOUT_INFLATER_SERVICE);

        View pop = Inf.inflate(R.layout.dialog_window_result_success, null);

        int width = LinearLayout.LayoutParams.WRAP_CONTENT;
        int height = LinearLayout.LayoutParams.WRAP_CONTENT;
        boolean focusable = true; // lets taps outside the popup also dismiss it
        final PopupWindow popupWindow = new PopupWindow(pop, width, height, focusable);

        closeButSuccessWindow = pop.findViewById(R.id.closeBtnSuccessWindow);

        popupWindow.showAtLocation(v, Gravity.CENTER, 0, 0);

        closeButSuccessWindow.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                popupWindow.dismiss();
            }
        });

    }

    public String GetDefaultDay()
    {
        return Integer.toString(Calendar.getInstance().get(Calendar.DAY_OF_WEEK));
    }

    public String GetDefaultMonth()
    {
        return Integer.toString(Calendar.getInstance().get(Calendar.MONTH));
    }
    public String GetDefaultYear()
    {
        return Integer.toString(Calendar.getInstance().get(Calendar.YEAR));
    }

}