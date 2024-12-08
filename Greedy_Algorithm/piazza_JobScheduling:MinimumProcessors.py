def minimum_processors(jobs):
    events = []
    for i, (start, end) in enumerate(jobs):
        events.append((start, 1, i + 1))  
        events.append((end, -1, i + 1)) 

    events.sort(key=lambda x: (x[0], x[1]))

    processors = []  
    scheduler_jobs = {} 
    job_to_processor = {}  

    max_processors = 0

    print("=== Job Scheduling 과정 ===")
    for time, event_type, job_id in events:
        if event_type == 1: 
            if processors:
                processor = processors.pop(0)
            else:
                processor = len(scheduler_jobs) + 1
                scheduler_jobs[processor] = []

            scheduler_jobs[processor].append(job_id)
            job_to_processor[job_id] = processor
            max_processors = max(max_processors, len(scheduler_jobs))
            print(f"시간 {time}: Job_{job_id} → Processor_{processor}")
        else: 
            processor = job_to_processor[job_id]
            processors.append(processor)
            processors.sort() 
            print(f"시간 {time}: Job_{job_id} 종료 → Processor_{processor} 해제")

    print("\n=== Scheduler Tasks ===")
    for processor, tasks in scheduler_jobs.items():
        print(f"Processor {processor}: Jobs {', '.join(f'Job_{job}' for job in tasks)}")

    return max_processors


jobs = [
    (38, 49), (28, 38), (14, 23), (10, 20), (21, 33),
    (22, 31), (47, 59), (13, 24), (25, 34), (35, 46),
    (41, 50), (3, 17), (17, 28), (5, 19), (26, 39),
    (37, 46), (8, 22), (32, 42), (24, 37), (40, 54)
]

min_processors = minimum_processors(jobs)
print(f"\n최소 필요한 프로세서 수: {min_processors}")
