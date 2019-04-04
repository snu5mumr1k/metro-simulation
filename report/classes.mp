input metauml;

beginfig(1);
    Class.Simulator("Simulator")
        ()
        ();
    Class.Metro("Metro")
        ()
        ();
    Class.Line("Line")
        ()
        ();
    Class.Station("Station")
        ()
        ();
    Class.Platform("Platform")
        ()
        ();
    Class.Section("Section")
        ()
        ();
    Class.Train("Train")
        ()
        ();
    Class.Path("Path")
        ()
        ();

    topToBottom(45)(Simulator, Metro, Line, Section);
    topToBottom(45)(Train, Path);
    topToBottom(45)(Station, Platform);
    leftToRight(45)(Train, Section, Station);

    drawObjects(
        Simulator,
        Metro,
        Line,
        Station,
        Platform,
        Section,
        Train,
        Path
    );

    clink(aggregation)(Section, Path);
    clink(aggregation)(Train, Line);
    clink(aggregationUni)(Path, Train);
    clink(aggregationUni)(Metro, Simulator);
    clink(composition)(Line, Metro);
    clink(composition)(Platform, Station);
    clink(composition)(Section, Line);
    clink(composition)(Station, Line);
    clink(dependency)(Train, Section);
    clink(dependency)(Section, Platform);
    clink(dependency)(Train, Platform);
endfig;
end
