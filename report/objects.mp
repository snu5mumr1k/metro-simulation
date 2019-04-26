input metauml;

beginfig(1);
    Instance.metro("metro: Metro")
        ();

    Instance.line("line: Line")
        ();

    Instance.station_zero("station: Station")("id = 0");
    Instance.station_one("station: Station")("id = 1");
    Instance.station_two("station: Station")("id = 2");
    Instance.station_three("station: Station")("id = 3");
    Instance.station_four("station: Station")("id = 4");

    Instance.platform_four_one("platform: Platform")("id = 9");
    Instance.platform_four_zero("platform: Platform")("id = 8");
    Instance.platform_three_one("platform: Platform")("id = 7");
    Instance.platform_three_zero("platform: Platform")("id = 6");
    Instance.platform_two_one("platform: Platform")("id = 5");
    Instance.platform_two_zero("platform: Platform")("id = 4");
    Instance.platform_one_one("platform: Platform")("id = 3");
    Instance.platform_one_zero("platform: Platform")("id = 2");
    Instance.platform_zero_one("platform: Platform")("id = 1");
    Instance.platform_zero_zero("platform: Platform")("id = 0");

    leftToRight(20)(metro, line, station_two, platform_two_one);
    topToBottom(40)(
        station_zero,
        station_one,
        station_two,
        station_three,
        station_four
    );

    topToBottom(20)(
        platform_zero_zero,
        platform_zero_one,
        platform_one_zero,
        platform_one_one,
        platform_two_zero,
        platform_two_one,
        platform_three_zero,
        platform_three_one,
        platform_four_zero,
        platform_four_one
    );

    drawObjects(
        metro,
        line,
        station_zero,
        station_one,
        station_two,
        station_three,
        station_four,
        platform_zero_zero,
        platform_zero_one,
        platform_one_zero,
        platform_one_one,
        platform_two_zero,
        platform_two_one,
        platform_three_zero,
        platform_three_one,
        platform_four_zero,
        platform_four_one
        );

    clink(aggregation)(line, metro);
    clink(aggregation)(station_zero, line);
    clink(aggregation)(station_one, line);
    clink(aggregation)(station_two, line);
    clink(aggregation)(station_three, line);
    clink(aggregation)(station_four, line);

    clink(aggregation)(platform_zero_zero, station_zero);
    clink(aggregation)(platform_zero_one, station_zero);
    clink(aggregation)(platform_one_zero, station_one);
    clink(aggregation)(platform_one_one, station_one);
    clink(aggregation)(platform_two_zero, station_two);
    clink(aggregation)(platform_two_one, station_two);
    clink(aggregation)(platform_three_zero, station_three);
    clink(aggregation)(platform_three_one, station_three);
    clink(aggregation)(platform_four_zero, station_four);
    clink(aggregation)(platform_four_one, station_four);

   draw platform_zero_zero.e
        .. (platform_zero_zero.e + platform_one_zero.e) / 2 + (20, 0)
        .. platform_one_zero.e;
    draw
        platform_one_zero.e
        .. (platform_one_zero.e + platform_two_zero.e) / 2 + (20, 0)
        .. platform_two_zero.e;
    draw
        platform_two_zero.e
        .. (platform_two_zero.e + platform_three_zero.e) / 2 + (20, 0)
        .. platform_three_zero.e;
    draw
        platform_three_zero.e
        .. (platform_three_zero.e + platform_four_zero.e) / 2 + (20, 0)
        .. platform_four_zero.e;
    draw
        platform_four_zero.e
        .. (platform_four_zero.e + platform_four_one.e) / 2 + (20, 0)
        .. platform_four_one.e;
    draw
        platform_four_one.e
        .. (platform_four_one.e + platform_three_one.e) / 2 + (20, 0)
        .. platform_three_one.e;
    draw
        platform_one_one.e
        .. (platform_one_one.e + platform_two_one.e) / 2 + (20, 0)
        .. platform_two_one.e;
    draw
        platform_two_one.e
        .. (platform_two_one.e + platform_three_one.e) / 2 + (20, 0)
        .. platform_three_one.e;
    draw
        platform_three_one.e
        .. (platform_three_one.e + platform_four_one.e) / 2 + (20, 0)
        .. platform_four_one.e;
    draw
        platform_one_one.e
        .. (platform_zero_one.e + platform_one_one.e) / 2 + (20, 0)
        .. platform_zero_one.e;
    draw
        platform_zero_one.e
        .. (platform_zero_zero.e + platform_zero_one.e) / 2 + (20, 0)
        .. platform_zero_zero.e;
endfig

end
