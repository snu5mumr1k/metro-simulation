input metauml;

beginfig(1);
    Class.Simulator("Simulator")
        (
            "- proto::Metro metro_data_",
            "- Metro metro_"
        )
        (
            "void Reset(const proto::Config &config)",
            "void Reset(proto::Metro metro_data)",
            "void Tick(const proto::Config &config)",
            "const proto::Metro &metro() const"
        );
    Class.Metro("Metro")
        (
            "- proto::Metro *metro_",
            "- std::vector<Line> lines_"
        )
        (
            "void Tick(const proto::Config &config)",
            "const proto::Metro &metro() const"
        );
    Class.Line("Line")
        (
            "- proto::Line *line_",
            "- std::unordered_map<int64_t, Section> sections_",
            "- std::unordered_map<int64_t, Station> stations_",
            "- std::unordered_map<int64_t, Platform> platforms_",
            "- std::unordered_map<int64_t, Train> trains_"
        )
        (
            "void Tick(const proto::Config &config)"
        );
    Class.Station("Station")
        (
            "- proto::Station *station_"
        )
        (
            "void Tick()"
        );
    Class.Platform("Platform")
        (
            "- proto::Platform *platform_"
        )
        (
            "void Tick()"
        );
    Class.Section("Section")
        (
            "- proto::Section *section_"
        )
        (
            "void Tick()",
            "const proto::Section &section() const"
        );
    Class.Train("Train")
        (
            "- proto::Train *train_",
            "- Path path_",
            "- std::optional<const Section> current_section_"
        )
        (
            "void Tick(const proto::Config &config)"
        );
    Class.Path("Path")
        (
            "- const proto::Path &path_",
            "- const std::unordered_map<int64_t, Section> &sections_"
        )
        (
            "std::optional<const Section> FindNextSection(int64_t platform_id) const"
        );

    topToBottom(45)(Section, Station, Platform);
    topToBottom(45)(Simulator, Metro, Line, Train, Path);
    leftToRight(45)(Line, Station);

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
