template<class Solver>
int handle_solver(ConfigReader &reader) {
    Solver solver(reader);
    try {
        solver.init();
        solver.info();
    } catch (std::exception &ex) {
        pprint::error << "handle_solver() caught error: " << ex.what();
        pprint::error(solver.prefix);
        return -1;
    }
    if (!is_confirmed("Run solver?")) return 0;

    while (solver.continue_to_run) {
        solver.do_step();
    }
    pprint::note << "Solver mainloop break.";
    pprint::note(solver.prefix);
    solver.do_save();
    return 0;
}

// 显示实例化
#ifdef INCLUDE_DUGKS_INCOMPRESSIBLE
template int handle_solver<DUGKS_INCOMPRESSIBLE>(ConfigReader &reader);
#endif
#ifdef INCLUDE_DUGKS_AOKI
template int handle_solver<DUGKS_AOKI>(ConfigReader &reader);
#endif